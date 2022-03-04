#pragma once


//---------------------------------------------------
#define GUI_INTERLOCK(channel,data)			\
extern "C" __declspec(dllexport) int SEQ_GUI_INTERLOCK(const CString& channel,const CString& data)

#define CHANNEL_INTERLOCK(channel,data)		\
extern "C" __declspec(dllexport) int SEQ_CHANNEL_INTERLOCK(const CString& channel,const CString& data)
//---------------------------------------------------

//---------------------------------------------------
#define SEQ_APP(app_name,app_para)			\
extern "C" __declspec(dllexport) void SEQ_THREAD_##app_name(const CStringArray& app_para)

#define SEQ_APP_CLOSE(app_name)				\
extern "C" __declspec(dllexport) void SEQ_THREAD_CLOSE_##app_name()
//---------------------------------------------------

//---------------------------------------------------
#define DRV_RS232__SET_PORT_INIT(port)		\
extern "C" __declspec(dllexport) int DRV_RS232__SET_PORT_INIT(const int port)

#define DRV_RS232__GET_PORT_INIT(p_rate,p_byte,p_stop,p_parity,p0,p1,p2,p3,p4,p5,p6,p7,p8,p9)	\
extern "C" __declspec(dllexport) int DRV_RS232__GET_PORT_INIT(int *p_rate,						\
															  int *p_byte,						\
															  int *p_stop,						\
															  int *p_parity,					\
															  const CString& p0,				\
															  const CString& p1,				\
															  const CString& p2,				\
															  const CString& p3,				\
															  const CString& p4,				\
															  const CString& p5,				\
															  const CString& p6,				\
															  const CString& p7,				\
															  const CString& p8,				\
															  const CString& p9)

#define DRV_RS232__SET_PROC(p_ch_info)		\
extern "C" __declspec(dllexport) int DRV_RS232__SET_PROC(CChannel_Info *p_ch_info)	

#define DRV_RS232__GET_PROC(p_ch_info)		\
extern "C" __declspec(dllexport) int DRV_RS232__GET_PROC(CChannel_Info *p_ch_info)	

#define DRV_RS232__CLOSE_PROC()				\
extern "C" __declspec(dllexport) int DRV_RS232__CLOSE_PROC()	
//---------------------------------------------------

//---------------------------------------------------
#define DRV_INTERFACE__INIT(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9)								\
extern "C" __declspec(dllexport) int DRV_INTERFACE__INIT(const CString& p0,				\
														 const CString& p1,				\
														 const CString& p2,				\
														 const CString& p3,				\
														 const CString& p4,				\
														 const CString& p5,				\
														 const CString& p6,				\
														 const CString& p7,				\
														 const CString& p8,				\
														 const CString& p9)
			
#define DRV_INTERFACE__SET_PROC(p_ch_info)		\
extern "C" __declspec(dllexport) int DRV_INTERFACE__SET_PROC(CChannel_Info *p_ch_info)

#define DRV_INTERFACE__GET_PROC(p_ch_info)		\
extern "C" __declspec(dllexport) int DRV_INTERFACE__GET_PROC(CChannel_Info *p_ch_info)

#define DRV_INTERFACE__CLOSE_PROC()				\
extern "C" __declspec(dllexport) int DRV_INTERFACE__CLOSE_PROC()
//---------------------------------------------------

//---------------------------------------------------
#define DRV_DEVICE_NET__INIT(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9)								\
extern "C" __declspec(dllexport) int DRV_DEVICE_NET__INIT(const CString& p0,			\
														  const CString& p1,			\
														  const CString& p2,			\
														  const CString& p3,			\
														  const CString& p4,			\
														  const CString& p5,			\
														  const CString& p6,			\
														  const CString& p7,			\
														  const CString& p8,			\
														  const CString& p9)
			
#define DRV_DEVICE_NET__SET_PROC(device_info,p_ch_info)		\
extern "C" __declspec(dllexport) int DRV_DEVICE_NET__SET_PROC(const CDeviceNet_Info_Ex& device_info,CChannel_Info *p_ch_info)

#define DRV_DEVICE_NET__GET_PROC(device_info,p_ch_info)		\
extern "C" __declspec(dllexport) int DRV_DEVICE_NET__GET_PROC(const CDeviceNet_Info_Ex& device_info,CChannel_Info *p_ch_info)

#define DRV_DEVICE_NET__CLOSE_PROC()				\
extern "C" __declspec(dllexport) int DRV_DEVICE_NET__CLOSE_PROC()
//---------------------------------------------------

//---------------------------------------------------
#define DRV_BOARD__INIT(board_id)			\
extern "C" __declspec(dllexport) int DRV_BOARD__INIT(const int board_id)

#define DRV_BOARD__SET_PROC(p_ch_info)		\
extern "C" __declspec(dllexport) int DRV_BOARD__SET_PROC(CChannel_Info *p_ch_info)

#define DRV_BOARD__GET_PROC(p_ch_info)		\
extern "C" __declspec(dllexport) int DRV_BOARD__GET_PROC(CChannel_Info *p_ch_info)

#define DRV_BOARD__CLOSE_PROC()				\
extern "C" __declspec(dllexport) int DRV_BOARD__CLOSE_PROC()
//---------------------------------------------------

//----------------------------------------------------
#define SEQ__START				\
	try							\
	{

#define SEQ__END				\
	}							\
	catch(int result)			\
	{							\
		return result;			\
	}							\
	return 1;

#define SEQ__OK					throw  1;
#define SEQ__ERROR				throw -1; 
//----------------------------------------------------
