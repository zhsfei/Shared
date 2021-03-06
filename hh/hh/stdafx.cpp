#include "stdafx.h"
#include "json/json_reader.cpp"
#include "json/json_value.cpp"
#include "json/json_writer.cpp"

#include "aoi/Entity.cpp"
#include "aoi/AOITrigger.cpp"
#include "aoi/CoordinateSystem.cpp"
#include "aoi/EntityCoordinateNode.cpp"
#include "aoi/EntityRef.cpp"
#include "aoi/RangeTrigger.cpp"
#include "aoi/RangeTriggerNode.cpp"
#include "aoi/Space.cpp"
#include "aoi/Witness.cpp"

#ifdef _DEBUG
//#pragma comment(lib,"../lib/libgame_d.lib")
#pragma comment(lib,"lib/libprotobuf_d.lib")
//#pragma comment(lib,"lib/libmysql.lib")
#else
#pragma comment(lib,"../lib/libgame.lib")
#pragma comment(lib,"../lib/libprotobuf.lib")
#pragma comment(lib,"../lib/libmysql.lib")
#endif // DEBUG