#pragma once
#include "Vector3.h"
#include <list>

namespace AOI
{
#define ENTITYREF_FLAG_UNKONWN							0x00000000
#define ENTITYREF_FLAG_ENTER_CLIENT_PENDING				0x00000001	// 进入客户端中标志
#define ENTITYREF_FLAG_LEAVE_CLIENT_PENDING				0x00000002	// 离开客户端中标志
#define ENTITYREF_FLAG_NORMAL							0x00000004	// 常规状态

	class CoordinateSystem;
	class EntityCoordinateNode;
	class Witness;
	class Space;

	enum EntityType
	{
		EntityTypePlayer,
		EntityTypeProps,
		EntityTypeNpc,
	};

	class Entity
	{
	public:
		Entity(int id, EntityType type);
		~Entity();
		Math::Vector3& position();
		void position(Math::Vector3& pos);

		EntityCoordinateNode* Entity::pEntityCoordinateNode() const;
		void Entity::pEntityCoordinateNode(EntityCoordinateNode* pNode);

		void installCoordinateNodes(CoordinateSystem* pCoordinateSystem);
		void uninstallCoordinateNodes(CoordinateSystem* pCoordinateSystem);

		/**
		进入离开space等回调
		*/
		virtual void onEnterSpace(Space* pSpace);
		virtual void onLeaveSpace(Space* pSpace);

		virtual void onOtherEntityMove(Entity* entity);

		/**
		观察者
		*/
		 Witness* pWitness() const;
		 void pWitness(Witness* w);

		 void setWitness(Witness* pWitness);

		/**
		自身被一个观察者观察到了
		*/
		void addWitnessed(Entity* entity);

		/**
		移除一个观察自身的观察者
		*/
		void delWitnessed(Entity* entity);

		std::list<int> GetWitnesses();

		int id();
		void id(int v);

		unsigned int flags();
		void flags(unsigned int v);

		EntityType& entityType();

		/**
		一个entity进入了AOI区域
		*/
		virtual void onEnteredAoI(Entity* entity);

        virtual void onLeaveAoI(Entity* entity);

	private:
		int id_;
		unsigned int											flags_;
		EntityType type_;

		EntityCoordinateNode* pEntityCoordinateNode_;
		CoordinateSystem* pCoordinateSystem_;
		Math::Vector3 position_;
		Math::Vector3 last_position_;

		// 是否被任何观察者监视到
		std::list<int>											witnesses_;
		size_t													witnesses_count_;

		// 观察者对象
		Witness*												pWitness_;
	};
}