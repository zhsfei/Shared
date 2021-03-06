#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <istream>
#include <iostream>
#include <ostream>

#include "icmp_header.h"
#include "ipv4_header.h"

#include <map>
using boost::asio::ip::icmp;
using boost::asio::deadline_timer;
namespace posix_time = boost::posix_time;

class pinger
{
public:
	pinger(boost::asio::io_service& io_service)
		: resolver_(io_service), socket_(io_service, icmp::v4()),
		timer_(io_service), sequence_number_(0), num_replies_(0)
	{
		start_receive();
	}

public:
	bool could_send_now()
	{

	}

	void start_send(const char* destination)
	{
		icmp::resolver::query query(icmp::v4(), destination, "");
		destination_ = resolver_.resolve(query);//目标地址
		if (destination_ == icmp::resolver::iterator())
		{
			return;
		}

		return;

		std::string body("\"Hello!\" from Asio ping.");

		// Create an ICMP header for an echo request.
		++sequence_number_;

		icmp_header echo_request;
		echo_request.type(icmp_header::echo_request);
		echo_request.code(0);
		echo_request.identifier(get_identifier());
		echo_request.sequence_number(sequence_number_);
		compute_checksum(echo_request, body.begin(), body.end());

		// Encode the request packet.
		boost::asio::streambuf request_buffer;
		std::ostream os(&request_buffer);
		os << echo_request << body;

		// Send the request.
		time_sent_ = posix_time::microsec_clock::universal_time();//boost 得到时间
		//start_receive();
		socket_.send_to(request_buffer.data(), *destination_);

		

		// Wait up to five seconds for a reply.
		num_replies_ = 0;
		//timer_.expires_at(time_sent_ + posix_time::seconds(5));
		//timer_.async_wait(boost::bind(&pinger::handle_timeout, this));
	}

private:
	void handle_timeout()
	{
		//if (num_replies_ == 0)
		//	std::cout << "Request timed out" << std::endl;

		// Requests must be sent no less than one second apart.
		//timer_.expires_at(time_sent_ + posix_time::seconds(1));
		//timer_.async_wait(boost::bind(&pinger::start_send, this));

		//start_receive();
	}

	void start_receive()
	{
		// Discard any data already in the buffer.
		reply_buffer_.consume(reply_buffer_.size());//streambuf.comsume()清空

		// Wait for a reply. We prepare the buffer to receive up to 64KB.
		socket_.async_receive(reply_buffer_.prepare(65536),//准备缓冲区
			boost::bind(&pinger::handle_receive, this, _1, _2));
	}

	void handle_receive(boost::system::error_code e, std::size_t length)
	{
		if (e)
		{
			//std::cout << e.message() << "\n";
			start_receive();
			return;
		}

		// The actual number of bytes received is committed to the buffer so that we
		// can extract it using a std::istream object.
		reply_buffer_.commit(length);//转移到streambuf中，


		// Decode the reply packet.
		std::istream is(&reply_buffer_);
		ipv4_header ipv4_hdr;
		icmp_header icmp_hdr;
		is >> ipv4_hdr >> icmp_hdr;

		// We can receive all ICMP packets received by the host, so we need to
		// filter out only the echo replies that match the our identifier and
		// expected sequence number.
		if (is && icmp_hdr.type() == icmp_header::echo_reply
			&& icmp_hdr.identifier() == get_identifier())
		{
			// If this is the first reply, interrupt the five second timeout.
			if (num_replies_++ == 0)
				timer_.cancel();

			// Print out some information about the reply packet.
			posix_time::ptime now = posix_time::microsec_clock::universal_time();
			std::cout << length - ipv4_hdr.header_length()
				<< " bytes from " << ipv4_hdr.source_address()
				<< ": icmp_seq=" << icmp_hdr.sequence_number()
				<< ", ttl=" << ipv4_hdr.time_to_live()
				<< ", time=" << (now - time_sent_).total_milliseconds() << " ms"
				<< std::endl;
		}

		start_receive();
	}

	static unsigned short get_identifier()
	{
#if defined(BOOST_ASIO_WINDOWS)
		return static_cast<unsigned short>(::GetCurrentProcessId());//全局函数，widows api，得到进程id
#else
		return static_cast<unsigned short>(::getpid());//linux
#endif
	}

	icmp::resolver resolver_;
	icmp::resolver::iterator destination_;
	icmp::socket socket_;
	deadline_timer timer_;
	unsigned short sequence_number_;
	posix_time::ptime time_sent_;
	boost::asio::streambuf reply_buffer_;
	std::size_t num_replies_;

	std::map<size_t, std::string> addr_;
};