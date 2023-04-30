#pragma once


#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__Utility_Link_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__Utility_Link_R.lib")
#endif


class SCI__Memory_Check
{
public:
	virtual ~SCI__Memory_Check(){};
	
	// ...
	virtual int Dump_To_File(const CString& path, const CString& log_title) = 0;
	
	// Core : DB_CTRL에서 제어 ...
	virtual int Clear__All_Memory_Info() = 0;

	virtual int Init__Dll_Resource() = 0;
};	


class SCI__THREAD_SYNC_CTRL
{
private:
	CRITICAL_SECTION mCS_LOCK;

public:
	SCI__THREAD_SYNC_CTRL()
	{
		InitializeCriticalSection(&mCS_LOCK);
	}
	~SCI__THREAD_SYNC_CTRL()
	{
		DeleteCriticalSection(&mCS_LOCK);
	}

	// ...
	void Thread__LOCK()
	{
		EnterCriticalSection(&mCS_LOCK);
	}
	void Thread__UNLOCK()
	{
		LeaveCriticalSection(&mCS_LOCK);
	}
};


class SCI__FILE_LINK_CTRL
{
public:
	virtual ~SCI__FILE_LINK_CTRL(){};

	// ...
	virtual int Set__Dir_Root(const CString& dir_root) = 0;
	virtual int Set__Key_Word(const CString& str_cmmd) = 0;
	virtual int Set__Para_Size(const int para_size) = 0;
	virtual int Disable__File_Log() = 0;

	virtual int Open(const CString& file_path) = 0;
	virtual int Read__File_Info() = 0;
	virtual int Close() = 0;

	virtual int Get__Item_List(CStringArray& l_item) = 0;
	virtual int Get__Item_List(CStringArray& l_para1,
				               CStringArray& l_para2) = 0;
	virtual int Get__Item_List(CStringArray& l_para1,
				               CStringArray& l_para2,
				               CStringArray& l_para3) = 0;	
	virtual int Get__Item_List(CStringArray& l_para1,
		                       CStringArray& l_para2,
							   CStringArray& l_para3,
		                       CStringArray& l_para4) = 0;	

	// ...
	virtual int Define__Delimiter_Character(const char ch) = 0;

	virtual int Get__Data_List_Of_Key_Word(const CString& key_word,
		                                   CStringArray& l_data) = 0;
};


class SCI__CHANNEL_CTRL
{
public:
	virtual ~SCI__CHANNEL_CTRL(){};

	// ...
	virtual int Get__CHANNEL_INFO(const CString& ch_name,int& obj_index,int& var_type,int& var_index) = 0;
	virtual int Get__CHANNEL_DATA(const int obj_index,const int var_type,const int var_index,CString& ch_data) = 0;

	virtual int Set__CHANNEL_DATA(const int obj_index,const int var_type,const int var_index,const CString& ch_data) = 0;
	virtual int Get__DIGITAL_ITEM_LIST(const int obj_index,const int var_type,const int var_index,CStringArray& l_item) = 0;

	virtual int Get__CHANNEL_INFO_EX(const CString& ch_name,int& obj_index,int& var_type,int& var_index,int& read_flag) = 0;

	// ...
	virtual int Check__CHANNEL_TYPE__ANALOG(const int var_type)  = 0;
	virtual int Check__CHANNEL_TYPE__DIGITAL(const int var_type) = 0;
	virtual int Check__CHANNEL_TYPE__STRING(const int var_type)  = 0;

    // ...
	virtual int Get__MIN_MAX_DEC_UNIT(const int obj_index,
									  const int var_type,
									  const int var_index,
									  double& min_value,
									  double& max_value,
									  int& i_dec,
									  CString& str_unit) = 0;
};


class SCI__OBJECT_VARIABLE_CTRL
{
public:
	virtual ~SCI__OBJECT_VARIABLE_CTRL(){};

	// ...
	virtual int Link__OBJECT(const CString& obj_name) = 0;

	virtual int Set__VARIABLE_DATA(const CString& var_name,const CString& var_data) = 0;
	virtual int Get__VARIABLE_DATA(const CString& var_name,CString& var_data) = 0;

	virtual int Check__VARIABLE_DATA(const CString& var_name,const CString& var_data) = 0;
	
	// ...
	virtual int When__VARIABLE_DATA(const CString& var_name,const CString& var_data,const double sec = 0.0) = 0;
	virtual int When__VARIABLE_DATA(const CString& var_name,const CStringArray& l_var_data,const double sec = 0.0) = 0;

	virtual int When__LESS_THAN(const CString& var_name,const double var_data,const double sec = 0.0) = 0;
	virtual int When__MORE_THAN(const CString& var_name,const double var_data,const double sec = 0.0) = 0;

	// ...	
	virtual int Get__SYNC_VARIABLE_DATA(const CString& var_name,CString& var_data) = 0;
	virtual int Check__SYNC_VARIABLE_DATA(const CString& var_name,const CString& var_data) = 0;
};

class SCI__OBJECT_ALARM_CTRL
{
public:
	virtual ~SCI__OBJECT_ALARM_CTRL(){};

	// ...
	virtual int Link__OBJECT(const CString& obj_name) = 0;

	// ...
	virtual int Popup__ALARM(const int id,CString& recovery_action) = 0;
	virtual int Post__ALARM(const int id) = 0;

	virtual int Check__ALARM(const int id,CString& recovery_action) = 0;
	virtual int Clear__ALARM(const int id) = 0;

	// ...
	virtual int Is__ALARM(const int id) = 0;

	virtual int Post__ALARM_WITH_BLOCKING(const int id,CString& recovery_action) = 0;
};


// Parity : None(0), Odd(1), Even(2), Mark(3), Space(4)

class SCI__SERIAL
{
public:
	virtual ~SCI__SERIAL(){};

	// ...
	virtual int INIT__COMPORT(const int port,
								const DWORD rate,
								const BYTE byte,
								const BYTE stop,
								const BYTE parity) = 0;

	virtual int CLEAR__BUFFER(CString* msg) = 0;
	virtual int OPEN__COMPORT()  = 0; 
	virtual int CLOSE__COMPORT() = 0;

	// ...
	virtual int DATA__SEND(const char* data) = 0;
	virtual int DATA__SEND(const CString& data) = 0;
	virtual int CHAR__SEND(unsigned char *data,const int length) = 0;

	// ...
	virtual int DATA__RECV(const char *end_str,char *data,const int msec) = 0;
	virtual int DATA__RECV(const char wait_ch,char *data,const char *end_str,const int msec) = 0;
	virtual int DATA__RECV(const char *wait_str,char *data,const char *end_str,const int msec) = 0;
	virtual int DATA__RECV(const char *w_str1,const char *w_str2,char *data,const char *end_str,const int msec) = 0;
	virtual int DATA__RECV(const CString& end_str,CString *data,const int msec) = 0;
	virtual int DATA__RECV(const char end_char,char *data,const int msec) = 0;
	virtual int DATA__RECV(const char end_char,CString *data,const int msec) = 0;
	
	virtual int CHAR__RECV(unsigned char *data,int *ret_cnt,const int msec) = 0;
	virtual int CHAR__RECV(const unsigned char wait_ch,unsigned char *data,int *ret_cnt,const int msec) = 0;
	virtual int CHAR__RECV(unsigned char *data,const unsigned char end_ch,int *ret_cnt,	const int msec) = 0;

	// ...
	virtual int RTS__ENABLE()  = 0;		// Default
	virtual int RTS__DISABLE() = 0;		
	virtual int DTR__ENABLE()  = 0;		// Default
	virtual int DTR__DISABLE() = 0;

	// ...
	virtual int INIT__COMPORT_WITHOUT_POPUP(const int port,
											const DWORD rate,
											const BYTE byte,
											const BYTE stop,
											const BYTE parity) = 0;

	// ...
	virtual int OnlyRecv__DATA(const char *end_str,char *data,const int msec) = 0;
	virtual int OnlyRecv__DATA(const char wait_ch,char *data,const char *end_str,const int msec) = 0;
	virtual int OnlyRecv__DATA(const char *wait_str,char *data,const char *end_str,const int msec) = 0;
	virtual int OnlyRecv__DATA(const char *w_str1,const char *w_str2,char *data,const char *end_str,const int msec) = 0;
	virtual int OnlyRecv__DATA(const CString& end_str,CString *data,const int msec) = 0;
	virtual int OnlyRecv__DATA(const char end_char,char *data,const int msec) = 0;
	virtual int OnlyRecv__DATA(const char end_char,CString *data,const int msec) = 0;

	virtual int OnlyRecv__CHAR(unsigned char *data,int *ret_cnt,const int msec) = 0;
	virtual int OnlyRecv__CHAR(const unsigned char wait_ch,unsigned char *data,int *ret_cnt,const int msec) = 0;
	virtual int OnlyRecv__CHAR(unsigned char *data,const unsigned char end_ch,int *ret_cnt,const int msec) = 0;

	// ...
	virtual int RTS__CHECK_SKIP() = 0;		
	virtual int DTR__CHECK_SKIP() = 0;		
};

class SCI__ASYNC_SERIAL
{
public:
	virtual ~SCI__ASYNC_SERIAL(){};

	// ...
	virtual int SET__TERMINAL_InSTRING(const char* in_term,const int size) = 0;
	virtual int SET__TERMINAL_OutSTRING(const char* out_term,const int size) = 0;

	// ...
	virtual int INIT__COMPORT(const int port,
								const DWORD rate,
								const BYTE byte,
								const BYTE stop,
								const BYTE parity) = 0;

	virtual int INIT__COMPORT_WITHOUT_POPUP(const int port,
											const DWORD rate,
											const BYTE byte,
											const BYTE stop,
											const BYTE parity) = 0;

	// ...
	virtual int OPEN__COMPORT()  = 0; 
	virtual int CLOSE__COMPORT() = 0;

	virtual int RTS__ENABLE()  = 0;		// Default
	virtual int RTS__DISABLE() = 0;		
	virtual int DTR__ENABLE()  = 0;		// Default
	virtual int DTR__DISABLE() = 0;

	// ...
	virtual int INIT__MSG_QUEUE() = 0;
	virtual int SET__MSG_QUEUE__PROPERTY(const int id_byte) = 0;

	virtual int RECV__QUEUE() = 0;

	virtual int GET__MSG_QUEUE(CString* msg) = 0;								// 0 <= : Data Length
	virtual int SEARCH__MSG_QUEUE(const CString& id_msg,CString* msg) = 0;		// 0 <= : Data Length

	// ...
	virtual int DATA__SEND(const char* data) = 0;
	virtual int DATA__SEND(const CString& data) = 0;
	virtual int CHAR__SEND(unsigned char *data,const int length) = 0;

	// ...
	virtual int RTS__CHECK_SKIP() = 0;		
	virtual int DTR__CHECK_SKIP() = 0;		
};

class SCI__SERIAL_JG
{
public:
	virtual ~SCI__SERIAL_JG(){};

	// ...
	virtual int INIT__COMPORT(const int port,
							  const DWORD rate,
							  const BYTE byte,
							  const BYTE stop,
							  const BYTE parity) = 0;
	virtual HANDLE Get__COMPORT_HANDLE() = 0;		// Error : INVALID_HANDLE_VALUE, 

	// ...
	virtual int CLEAR__BUFFER(CString* msg)    = 0;
	virtual int OPEN__COMPORT()  = 0; 
	virtual int CLOSE__COMPORT() = 0;

	virtual int DATA__SEND(const char* data) = 0;
	virtual int DATA__SEND(const CString& data) = 0;
	virtual int CHAR__SEND(unsigned char *data,
						   const int length) = 0;
	
	virtual int DATA__RECV(const char *end_str,
						   char *data,
						   const int msec) = 0;
	virtual int DATA__RECV(const char wait_ch,
						   char *data,
						   const char *end_str,
						   const int msec) = 0;
	virtual int DATA__RECV(const char *wait_str,
						   char *data,
						   const char *end_str,
						   const int msec) = 0;
	virtual int DATA__RECV(const char *w_str1,
						   const char *w_str2,
						   char *data,
						   const char *end_str,
						   const int msec) = 0;
	virtual int DATA__RECV(const CString& end_str,
						   CString *data,
						   const int msec) = 0;
	virtual int DATA__RECV(const char end_char,
						   char *data,
						   const int msec) = 0;
	virtual int DATA__RECV(const char end_char,
						   CString *data,
						   const int msec) = 0;

	virtual int CHAR__RECV(unsigned char *data,
						   int *ret_cnt,
						   const int msec) = 0;
	virtual int CHAR__RECV(const unsigned char wait_ch,
						   unsigned char *data,
						   int *ret_cnt,
						   const int msec) = 0;
	virtual int CHAR__RECV(unsigned char *data,
						   const unsigned char end_ch,
						   int *ret_cnt,
						   const int msec) = 0;

	virtual int RTS__ENABLE()  = 0;		// Default
	virtual int RTS__DISABLE() = 0;		
	virtual int DTR__ENABLE()  = 0;		// Default
	virtual int DTR__DISABLE() = 0;

	// ...
	virtual int INIT__COMPORT_WITHOUT_POPUP(const int port,
											const DWORD rate,
										    const BYTE byte,
											const BYTE stop,
											const BYTE parity) = 0;

	virtual int OnlyRecv__DATA(const char *end_str,
							   char *data,
							   const int msec) = 0;
	virtual int OnlyRecv__DATA(const char wait_ch,
							   char *data,
							   const char *end_str,
							   const int msec) = 0;
	virtual int OnlyRecv__DATA(const char *wait_str,
							   char *data,
							   const char *end_str,
							   const int msec) = 0;
	virtual int OnlyRecv__DATA(const char *w_str1,
							   const char *w_str2,
							   char *data,
							   const char *end_str,
							   const int msec) = 0;
	virtual int OnlyRecv__DATA(const CString& end_str,
							   CString *data,
							   const int msec) = 0;
	virtual int OnlyRecv__DATA(const char end_char,
							   char *data,
							   const int msec) = 0;
	virtual int OnlyRecv__DATA(const char end_char,
							   CString *data,
							   const int msec) = 0;
	virtual int OnlyRecv__CHAR(unsigned char *data,
							   int *ret_cnt,
							   const int msec) = 0;
	virtual int OnlyRecv__CHAR(const unsigned char wait_ch,
							   unsigned char *data,
							   int *ret_cnt,
							   const int msec) = 0;
	virtual int OnlyRecv__CHAR(unsigned char *data,
							   const unsigned char end_ch,
							   int *ret_cnt,
							   const int msec) = 0;

	// ...
	virtual int Link__COMPORT_HANDLE(const HANDLE h_comm) = 0;		

	virtual int RTS__CHECK_SKIP() = 0;		
	virtual int DTR__CHECK_SKIP() = 0;		

	// ...
	virtual int INIT__COMPORT_EX(const int port,
								 const DWORD rate,
								 const BYTE byte,
								 const BYTE stop,
								 const BYTE parity,
								 const int rts,			// > 0 : ENABLE, < 1 : DIABLE 
								 const int dtr) = 0;	// > 0 : ENABLE, < 1 : DIABLE 
};

class SCI__COM_PORT
{
public:
	virtual ~SCI__COM_PORT(){};

	// ...
	virtual int INIT__COMPORT(const int port,
							  const DWORD rate,
							  const BYTE byte,
							  const BYTE stop,
							  const BYTE parity) = 0;

	virtual int INIT__COMPORT_EX(const int port,
								 const DWORD rate,
								 const BYTE byte,
								 const BYTE stop,
								 const BYTE parity,
								 const int rts,			// > 0 : ENABLE, < 1 : DIABLE 
								 const int dtr) = 0;	// > 0 : ENABLE, < 1 : DIABLE 

	// ...
	virtual int CLEAR__BUFFER()  = 0;
	virtual int OPEN__COMPORT()  = 0; 
	virtual int CLOSE__COMPORT() = 0;

	virtual int RTS__ENABLE()  = 0;		// Default
	virtual int RTS__DISABLE() = 0;		
	virtual int DTR__ENABLE()  = 0;		// Default
	virtual int DTR__DISABLE() = 0;

	virtual int RTS__CHECK_SKIP() = 0;		
	virtual int DTR__CHECK_SKIP() = 0;		

	// ...
	virtual int Send__CHAR(unsigned char *data,
						   const int length) = 0;
	
	virtual int OnlyRecv__CHAR(unsigned char *data,
							   int *ret_cnt,
							   const int msec) = 0;
};


// ...
class SCI__ETHERNET_JGLEE
{
public:
	virtual ~SCI__ETHERNET_JGLEE(){};
	
	// ...
	virtual int  INIT__PROPERTY(const CString& ip,
								const int port) = 0;

	virtual int  SET__TERMINAL_InSTRING(const char* in_term,
		                                const int size) = 0;
	virtual int  SET__TERMINAL_OutSTRING(const char* out_term,
		                                 const int size) = 0;

	// ...
	virtual int  SET__ETHERNET_TYPE__CLIENT() = 0;		// Default Type
	virtual int  SET__ETHERNET_TYPE__SERVER() = 0;		
	
	virtual int  START__SERVER() = 0;					// 함수 호출 이후에는 ETHERNET TYPE 변경 불가함.  
	virtual int  CONNECT(CString *msg) = 0;
	
	virtual CString GET__CURRENT_ETHERNET_TYPE() = 0;

	// ...
	virtual int  DATA__SEND(CString *data,
		                    const int sec) = 0;
	virtual int  DATA__SEND(CString *data,
		                    const int data_size,
		                    const int sec) = 0;

	virtual int  CLEAR__BUFFER(CString *msg) = 0;
		
	virtual int  DISCONNECT() = 0;
	
	// ...
	virtual int  IS_CONNECT() = 0;
	
	// ...
	virtual int  DATA__SEND(const CString& send_data,
		                    const int sec,
		                    CString *error) = 0;		// -1 : Timeout or Socket Error,  1 : Success
	
	virtual int  DATA__RECV(CString *recv_data,
		                    const int sec,
		                    CString *error) = 0;      	// -1 : Timeout,  0 <= : Data Length
	virtual int  DATA__RECV_QUEUE(CString *recv_data,
							const int sec,
							CString *error) = 0;      	// -1 : Timeout,  0 <= : Data Length
	
	// ...
	virtual int  CHAR__SEND(const CString& data,
		                    const int char_len,
		                    const int sec,
		                    CString *error) = 0;		// -1 : Timeout or Socket Error,  1 : Success
	virtual int  CHAR__RECV(CString *data,
		                    const int char_len,
		                    const int sec,
		                    CString *error) = 0;   		// -1 : Timeout,  0 <= : Data Length
	
	// ...
	virtual int  CHAR__SEND(const char* data,
		                    const int char_len,
		                    const int sec,
		                    CString *error) = 0;		// -1 : Timeout or Socket Error,  1 : Success
	virtual int  CHAR__RECV(char* data,
		                    const int char_len,
		                    const int sec,
		                    CString *error) = 0;   		// -1 : Timeout,  0 <= : Data Length
	
	// ...
	virtual int  INIT__MSG_QUEUE() = 0;
	virtual int  SET__MSG_QUEUE__PROPERTY(const int id_byte) = 0;
	
	virtual int  RECV__QUEUE() = 0;
	
	virtual int  GET__MSG_QUEUE(CString* msg) = 0;				// 0 <= : Data Length
	virtual int  SEARCH__MSG_QUEUE(const CString& id_msg,		// 0 <= : Data Length
		                           CString* msg) = 0;
	
	// ...
	virtual int  CLEAR__MEM_BUFFER(CString *msg) = 0;
	
	virtual int  READ__NETWORK_BUFFER(char *recv_data,
		                              const int char_len) = 0;  	// -1 : Connection Error, or Return char_len
	
	// ...
	virtual int  IS_CONNECT_EX() = 0;	

	virtual CString GET__TERMINAL_InSTRING() = 0;
	virtual CString GET__TERMINAL_OutSTRING() = 0;
};


// ...
typedef int (*FNC_ETHERNET_SERVER)(LPVOID p_void,CString *data);
typedef int (*FNC_ETHERNET_SERVER__NON_TERMINAL)(LPVOID p_void,CString *data,int* char_byte);


class SCI__ETHERNET_SERVER_JGLEE
{
public:
	virtual ~SCI__ETHERNET_SERVER_JGLEE(){};
	
	// ...
	virtual int  SET__PROPERTY(const CString& ip_address,
		                       const int port) = 0;
	virtual int  SET__TERMINAL_InSTRING(const char* in_term,
		                                const int size) = 0;
	virtual int  SET__TERMINAL_OutSTRING(const char* out_term,
		                                 const int size) = 0;
	
	virtual int  SET__USER_SERVER(LPVOID p_class,
		                          FNC_ETHERNET_SERVER p_fnc) = 0;
	
	virtual int  SET__NON_TERMINAL_TYPE() = 0;
	virtual int  SET__USER_SERVER(LPVOID p_class,
		                          FNC_ETHERNET_SERVER__NON_TERMINAL p_fnc,
		                          const int read_byte) = 0;
	
	// ...
	virtual int SET__ETHERNET_TYPE__SERVER() = 0;		// Default Type
	virtual int SET__ETHERNET_TYPE__CLIENT() = 0;		
	
	virtual int  START__SERVER() = 0;					// 함수 호출 이후에는 ETHERNET TYPE 변경 불가함.  	

	virtual CString GET__CURRENT_ETHERNET_TYPE() = 0;	

	// ...
	virtual int SEND__MSG_TO_CLIENT(const CString& s_data) = 0;

	virtual CString GET__TERMINAL_InSTRING() = 0;
	virtual CString GET__TERMINAL_OutSTRING() = 0;

	// ...
	virtual bool IS__CONNECTED() = 0;
};


// ...
class SCI__USER_LOG_CTRL
{
public:
	virtual ~SCI__USER_LOG_CTRL(){};

	// ...
	virtual int CREATE__SUB_DIRECTORY(const CString& sub_dir) = 0;
	virtual int SET__PROPERTY(const CString& file_name,
							  const int file_size,
							  const int file_time) = 0;

	virtual int WRITE__LOG(const CString& log_msg) = 0;
	virtual int WRITE__LOG(const CString& level,const CString& log_msg) = 0;

	virtual int ENABLE__TIME_LOG()  = 0;
	virtual int DISABLE__TIME_LOG() = 0;

	virtual int LINK__OBJECT(const CString& obj_name) = 0;

	// ...
	virtual int Write__Right_Now() = 0;

	
	// ...
	// Standard Process Log ...
	virtual int STD_Process_Log(const CString& deviceid,
								const CString& eventid,
								const CString& status,
								const CString& materialid,
								const int slot_num,
								const CString& lotid,
								const CString& recipeid,
								const int step_num,
								const CStringArray& l_key,
								const CStringArray& l_value) = 0;

	// Standard Transfer Log ...
	virtual int STD_Transfer_Log(const CString& deviceid,
								 const CString& eventid,
								 const CString& status,
								 const CString& materialid,
								 const CString& material_type,
								 const CString& from_device,
								 const int from_slot,
								 const CString& to_device,
								 const int to_slot,
								 const CStringArray& l_key,
								 const CStringArray& l_value) = 0;
	
	// Standard Function Log ...
	virtual	int STD_Function_Log(const CString& deviceid,
								 const CString& eventid,
								 const CString& status,
								 const CString& materialid,
								 const CString& material_type,
								 const CStringArray& l_key,
								 const CStringArray& l_value) = 0;
	
	// Standard Lot Event Log ...
	virtual int STD_Lot_Event_Log(const CString& deviceid,
								  const CString& eventid,
								  const CString& lotid,
								  const CString& flow_recipeid,
								  const CString& flow_info,
								  const CString& carrierid,
								  const CStringArray& l_key,
								  const CStringArray& l_value) = 0;

	// ...
	virtual int Attach__Date_And_Time_To_Log_Name()  = 0;
};

class SCI__FILE_CTRL
{
public:
	virtual ~SCI__FILE_CTRL(){};

	// ...
	virtual int Init__FILE(const CString& path) = 0;

	virtual int Write__LOG(const CString& string) = 0;
	virtual int Write__LOG(const CString& title,const CString& string) = 0;

	// command  :  DAY, HOUR, MINUTE, FILE_LIMIT
	// Default  :  DAY=1, FILE_LIMIT=30
	virtual int SET__PROPERTY(const CString& command,const CString& para_data) = 0;

	virtual int ENABLE__TIME_LOG()  = 0;
	virtual int DISABLE__TIME_LOG() = 0;

	
	// ...
	virtual int Delete__LOG_DIR(const CString& dir_root,const int day_count) = 0;

	virtual int Create__LOG_DIR(const CString& dir_log) = 0;
	virtual int Write__LOG_MSG(const CString& log_path,const CString& log_msg) = 0;

	// ...
	virtual int Write__Right_Now() = 0;
};

class SCI__COMMON_FILE_CTRL
{
public:
	virtual ~SCI__COMMON_FILE_CTRL(){};

	// ...
	// command  :  DAY, HOUR, MINUTE, FILE_LIMIT
	// Default  :  DAY=1, FILE_LIMIT=30
	virtual int SET__PROPERTY(const CString& command,const CString& para_data) = 0;

	// ...
	virtual int Write__LOG(const CString& str_log) = 0;
	virtual int Write__LOG(const CString& str_level,const CString& str_log) = 0;

	// ...
	virtual int SET__OBJ_NAME(const CString& obj_name) = 0;
};


// ...
class SCI__STEP_TIMER_CTRL
{
public:
	virtual ~SCI__STEP_TIMER_CTRL(){};

	// ...
	virtual void START__TIMER() = 0;

	virtual bool Check__CURRENT_TIME(const double ref_sec, double& cur_sec) = 0;
	virtual double Get__CURRENT_SEC() = 0;

	// ...
	virtual void Enable__QUERY_COUNT(const double offset_sec = -1.0) = 0;   // default
	virtual void Enable__TICK_COUNT(const double offset_sec = -1.0)  = 0;
};


// ...
typedef int (*FNC_CHECK)(CString *data);
typedef int (*FNC_CHECK_CHAR)(char *data,int *length);


class SCI__TIMER_CTRL
{
public:
	virtual ~SCI__TIMER_CTRL(){};

	// ...
	virtual int REGISTER__COUNT_CHANNEL(const CString& object_name,
										const CString& variable_name) = 0;
	virtual int REGISTER__ABORT_OBJECT(const CString& object_name) = 0;

	virtual int REGISTER__COUNT_CHANNEL(const CString& ch_name) = 0;
	virtual int REGISTER__ABORT_CHANNEL(const CString& ch_name) = 0;


	virtual int INIT__COUNT_UP() = 0;
	virtual int INIT__COUNT_DOWN() = 0;

	virtual int WAIT(const double sec) = 0;
	virtual int POLL(const double sec) = 0;

	// ...
	virtual int SET__DECIMAL_POINT(const int dec_point) = 0;
};


// ...
class SCI__ASYNC_TIMER_CTRL
{
public:
	virtual ~SCI__ASYNC_TIMER_CTRL(){};

	// ...
	virtual int REGISTER__COUNT_CHANNEL(const CString& object_name,
									    const CString& variable_name) = 0;

	virtual int START__COUNT_DOWN(const double sec) = 0;
	virtual int START__COUNT_UP(const double sec) = 0;

	virtual double Get__CURRENT_TIME() = 0;

	virtual int STOP() = 0;
	virtual int PAUSE() = 0;
	virtual int RESUME() = 0;

	virtual int Get__TIMER_SIZE() = 0;
	virtual int Get__TIMER_INDEX() = 0;

	virtual int REGISTER__COUNT_CHANNEL_NAME(const CString& ch_name) = 0;

	virtual int Set__START_TIME(const double init_sec) = 0;
	virtual int Get__TIMER_DB_MAX_SIZE() = 0;

	// ...
	virtual int STOP_ZERO() = 0;

	// ...
	virtual int INIT__STOPWATCH() = 0;
	virtual double GET_mSEC__STOPWATCH() = 0;
	virtual double GET_SEC__STOPWATCH()  = 0;
};


// ...
class SCI__ALARM_CTRL
{
public:
	virtual ~SCI__ALARM_CTRL(){};

	// ...
	virtual int Register__ALARM_ID(const int alarm_id) = 0;

	
	virtual int Post__ALARM(const CString& title,
							const CString& message,
							const CString& option) = 0;
	virtual int Post__ALARM(const CString& title,
							const CString& message,
							const CStringArray& l_option) = 0;
	
	virtual	int Check__ALARM(CString& act_result) = 0;

	virtual int Popup__ALARM(const CString& title,
							 const CString& message,
							 const CString& option,
							 CString& act_result) = 0;
	virtual int Popup__ALARM(const CString& title,
							 const CString& message,
							 const CStringArray& l_option,
							 CString& act_result) = 0;

	virtual int Get__POST_ALARM(const int db_index,
								CString *module,
								CString *alarm_type,
								CString *time,  
								CString *alarm_id,
								CString *title, 
								CString *message,
								CStringArray *l_option) = 0;

	virtual int Get__CLEAR_ALARM(CString *module,
								 CString *alarm_type,
							     CString *time,  
								 CString *alarm_id,
							     CString *title, 
								 CString *act_result) = 0;

	virtual int Is__SIZE() = 0;

	
	virtual int Update__POST_ALARM(const CString& title,
								   const CString& message,
								   const CStringArray& l_option) = 0;

	virtual int Post__WARNING(const CString& title,
							  const CString& message,
							  const CStringArray& l_option) = 0;

	virtual int Update__POST_WARNING(const CString& title,
									 const CString& message,
									 const CStringArray& l_option) = 0;

	// ...
	virtual int Clear__MODULE_ALARM(const CString& module) = 0;

	virtual int Get__ALARM_MODULE_LIST(CUIntArray& l_seqid) = 0;
	
	// ...
	virtual int Get__POSTED_ALARM_INFO(const int db_index,
					  		           int& seq_id,
									   int& alarm_type,
									   int& alarm_id,
									   CString& time,
									   CString& title,
									   CString& message,
									   CStringArray& l_option) = 0;

	virtual int Get__LAST_POSTED_ALARM_INFO(int& seq_id,
									        int& alarm_type,
									        int& alarm_id,
									        CString& time,
									        CString& title,
									        CString& message,
									        CStringArray& l_option) = 0;


	// ...
	virtual int ALARM_LOG_DB__Load_POST_INFO(const int seq_id,
											 const int alarm_id,
											 const CString& alarm_time,
											 const CString& alarm_title,
											 const CString& alarm_message,
											 const CStringArray& l_option) = 0;

	virtual int ALARM_LOG_DB__Load_CLEAR_INFO(const int seq_id,
											  const int alarm_id,
											  const CString& alarm_time,
											  const CString& alarm_title,
											  const CString& alarm_message,
											  const CString& r_act) = 0;

	virtual int ALARM_LOG_DB__Get_INFO(int& alm_post_flag,
									   int& seq_id,
									   int& alarm_id,
									   CString& alarm_time,
									   CString& alarm_title,
									   CString& alarm_message,
									   CStringArray& l_option,
									   CString& r_act) = 0;

	// ...
	virtual int Get__POST_ALARM_EX(const int db_index,
								   CString& ref_toolid,
								   CString& ref_unitid,
							       int& host_report,
								   int& alarm_level,
								   CString *module,
								   CString *alarm_type,
								   CString *time,  
								   CString *alarm_id,
								   CString *title, 
								   CString *message,
								   CStringArray *l_option) = 0;

	virtual int Reload__ALARM_DB() = 0;

	virtual int Get__CLEAR_ALARM_EX(CString& ref_toolid,
									CString& ref_unitid,
									int& host_report,
									int& alarm_level,
								    CString *module,
						   		    CString *alarm_type,
									CString *time,  
									CString *alarm_id,
									CString *title, 
									CString *act_result) = 0;

	// ...
	virtual int Reload__ALARM_LEVEL() = 0;

	// ...
	virtual int Is__SIZE_EXCEPT_MSG_BOX() = 0;
	
	virtual int Is__HEAVY_ALARM_SIZE() = 0;
	virtual int Is__LIGHT_ALARM_SIZE() = 0;
	virtual int Is__WARNING_ALARM_SIZE() = 0;

	// ...
	virtual int ALARM_LOG_DB__Load_POST_EX(const int seq_id,
										   const int alarm_id,
										   const int alarm_level,
										   const CString& alarm_time,
										   const CString& alarm_title,
										   const CString& alarm_message,
										   const CStringArray& l_option) = 0;

	virtual int ALARM_LOG_DB__Load_CLEAR_EX(const int seq_id,
										    const int alarm_id,
										    const int alarm_level,
											const CString& alarm_time,
										    const CString& alarm_title,
										    const CString& alarm_message,
										    const CString& r_act) = 0;

	virtual int ALARM_LOG_DB__Get_INFO_EX(int& alm_post_flag,
										  int& seq_id,
										  int& alarm_id,
										  int& alarm_level,
										  CString& alarm_time,
										  CString& alarm_title,
										  CString& alarm_message,
										  CStringArray& l_option,
										  CString& r_act) = 0;

	// ...
	virtual int Get__Posted_All_Alarm(CUIntArray& l_ext_id) = 0;
	virtual int Get__Posted_Heavy_Alarm(CUIntArray& l_ext_id) = 0;

	virtual int Get__Posted_Alarm_Level(const int ext_id, 
										int& eqp_id,
										CString& alm_level) = 0;
	virtual int Get__Posted_Alarm_Level(const int ext_id, 
									   int& eqp_id,
									   CString& obj_name,
									   int& internal_id,
									   CString& alm_level,
									   CString& alm_title) = 0;
};


// ...
class SCI__RECIPE_FILE
{
public:
	virtual ~SCI__RECIPE_FILE(){};

	// ...
	virtual int  Upload__FILE(const CString& file) = 0;

	virtual void Free__MEM() = 0;
	virtual int  Read__MEM() = 0;

	virtual int  Jump__STEP_NO(const int step_no) = 0;

	// ...
	virtual int  Get__TOTAL_STEP_SIZE() = 0;
	virtual int  Get__STEP_ITEM_INFO(CStringArray& l_ch_name,
									 CStringArray& l_ch_data) = 0;

	// ...
	virtual int  Get__CUR_STEP_NO() = 0;	
	virtual int  Get__HEADER_RECIPE_INFO(const CStringArray& l_ch_name,
										 CStringArray& l_ch_data) = 0;

	// ...
	virtual int  Get__ITEM_INFO_OF_RECIPE_STEPx(const int step_index,
		                                        const CStringArray& l_ch_name,
		                                        CStringArray& l_ch_data) = 0;

	virtual int  Check__STEP_ITEM_CHECK(int& ref_item_num,
		                                int& err_step,
		                                int& err_item_num,
		                                CUIntArray& l_step_item_size) = 0;
	
	// ...
	virtual int  Link__APC_INFO(const CString& apc_info) = 0;
	virtual int  Clear__APC_INFO() = 0;

	// ....
	virtual int  Define__Conversion_Object_Name(const CString& src_obj,
		                                        const CString& trg_obj) = 0;
};


class SCI__FILE_RCP_CTRL
{
public:
	virtual ~SCI__FILE_RCP_CTRL(){};

	// ...
	virtual int Create__FILE(const CString& path) = 0;
	virtual int Close__FILE() = 0;

	virtual int Save__FILE() = 0;
	virtual int Delete__FILE(const CString& path) = 0;

	virtual int Check__FILE(const CString& path) = 0;

	virtual int Add__ITEM(const CString& channel_name,
						  const CString& channel_type,
						  const CString& data) = 0;

	virtual int Go__NEXT_STEP() = 0;

	// ...
	virtual int Partial__INIT_FILE(const CString& path) = 0;
	virtual int Partial__STEP_JUMP(const int step) = 0;
	virtual int Partial__ADD_ITEM(const CString& channel_name,
								  const CString& channel_type,
								  const CString& data) = 0;
	virtual int Partial__SAVE_FILE(const CString& path) = 0;

	// ...
	virtual int Create__REMOTE_FILE() = 0;

	virtual int Close__REMOTE_FILE() = 0;
	virtual int Save__REMOTE_FILE(const int& seq_id,
								  const CString& sub_dir,
								  const CString& file_name,
								  const CString& file_ext) = 0;

	// ...
	virtual int Check__REMOTE_FILE(const int& seq_id,
								   const CString& sub_dir,
								   const CString& file_name,
								   const CString& file_ext) = 0;

	virtual int Partial__INIT_REMOTE_FILE(const int& seq_id,
										  const CString& sub_dir,
										  const CString& file_name,
										  const CString& file_ext) = 0;
	virtual int Partial__STEP_REMOTE_FILE(const int& step) = 0;
	virtual int Partial__ITEM_REMOTE_FILE(const CString& channel_name,
										  const CString& channel_type,
										  const CString& data) = 0;
	virtual int Partial__SAVE_REMOTE_FILE(const int& seq_id,
										  const CString& sub_dir,
										  const CString& file_name,
										  const CString& file_ext) = 0;

	// ...
	virtual int Delete__REMOTE_FILE(const int seq_id,
								    const CString& sub_dir,
									const CString& file_name,
									const CString& file_ext) = 0;
	virtual int Rename__REMOTE_FILE(const int seq_id,
									const CString& sub_dir,
									const CString& file_ext,
									const CString& src_file,
									const CString& trg_file) = 0;
};


class SCI__FILE_RCP_INFO
{
public:
	virtual ~SCI__FILE_RCP_INFO(){};

	// ...
	virtual int Upload__FILE(const CString& path) = 0;
	virtual int Clear__MEM() = 0;

	virtual int Get__STEP_SIZE() = 0;
	virtual int Get__ITEM_DATA(const int step_index,
							   const CString& ch_name,
							   CString& data) = 0;

	virtual int Check__FILE(const CString& path) = 0;

	// ...
	virtual int Upload__REMOTE_FILE(const int& seq_id,
								    const CString& sub_dir,
								    const CString& file_name,
								    const CString& file_ext) = 0;

	virtual int Search__REMOTE_FILE_LIST(const int& seq_id,
										 const CString& sub_dir,
										 const CString& file_ext,
										 CStringArray& l_file_name) = 0;

	// ...
	virtual int Search__REMOTE_DIR_LIST(const int& seq_id,
										CStringArray& l_dir) = 0;

	virtual int Search__REMOTE_ALL_FILE_LIST(const int& seq_id,
										     const CString& file_ext,
										     CStringArray&  l_file_name) = 0;

	// ...
	virtual int Get__REMOTE_FILE_DATE_INFO(const int& seq_id,
										   const CString& file_ext,
										   const CStringArray& l_file_name,
										   CStringArray& l_file_date) = 0;

	// ...
	virtual CString Get__REMOTE_FILE_DATA(const int& seq_id,
										  const CString& sub_dir,
										  const CString& file_name,
										  const CString& file_ext) = 0;

	virtual int Upload__REMOTE_FILE_AND_Get__FILE_DATA(const int& seq_id,
									                   const CString& sub_dir,
								                       const CString& file_name,
								                       const CString& file_ext,
													   CString& file_data) = 0;

	virtual int Get__FILE_DB__ERROR_MESSAGE(CString& err_msg) = 0;
};


// ...
class CDS__ROUTE_PMC_INFO
{
public:
	void Init__DB()
	{
		iMODULE_ID = 0;
		sMODULE_RECIPE = "";
	}

	int     iMODULE_ID;			// PM1 - 1, ..., PM6 - 6
	CString sMODULE_RECIPE;
};


class CDS__POST_CLN_INFO
{
public:
	CDS__POST_CLN_INFO()	
	{
		iMODULE_ID     = 0;
		sPOSTCLN_RECIPE = "";
	}
	
	int     iMODULE_ID;			// PM1 - 1, ..., PM6 - 6
	CString sPOSTCLN_RECIPE;
};

//-------------------------------------------------------------------------------------------
// TYPE : ADDED
// OWNER : buyong.chang
// NOTE :  PostClean 정보와 Clean_LL정보를 HOST로 보고하지 않아 추가함

class CDS__ROUTE_CLN_LL_INFO
{
public:
	CDS__ROUTE_CLN_LL_INFO()	
	{
		sCL1_RcpName = sCL2_RcpName = "";
	}
	
	CString	sCL1_RcpName;
	CString	sCL2_RcpName;
};

class CDS__ROUTE_POST_CLN_INFO
{
public:
	CDS__ROUTE_POST_CLN_INFO()	
	{
		iMODULE_ID	   = 0;
		sMODULE_RECIPE = "";
	}
	
	int     iMODULE_ID;			// PM1 - 1, ..., PM6 - 6
	CString sMODULE_RECIPE;
};
//-------------------------------------------------------------------------------------------


class SCI__FILE_ROUTE_INFO
{
public:
	virtual ~SCI__FILE_ROUTE_INFO(){};

	// ...
	virtual int Upload__FILE(const CString& path) = 0;
	virtual int Clear__MEM() = 0;

	virtual int Get__ROUTE_SERIAL_STEP_SIZE() = 0;
	virtual int Get__ROUTE_PARALLEL_PATH_SIZE(const int serial_step_index) = 0;

	virtual int Get__PMC_INFO(const int serial_step_index,
							  const int parallel_path_index,
						      CDS__ROUTE_PMC_INFO& pmc_info) = 0;

	virtual int Check__FILE(const CString& path) = 0;

	// ...
	virtual double Get__Cooling_Time() = 0;
	virtual double Get__Preheat_Time() = 0;

	// ...
	virtual int Get__PMC_LIST_OF_FIRST_STEP(CUIntArray& l_pmc_id,
											CStringArray& l_pmc_rcp) = 0;

	virtual CString Get__VISION_RECIPE_NAME() = 0;

	// ...
	virtual int Upload__FILE_WITH_MULTI_STEP(const CString& path) = 0;
	virtual int Get__DATA_BYTE_SIZE() = 0;
};

class SCI__FILE_ROUTE_INFO__ETCHER_QUAD
{
public:
	virtual ~SCI__FILE_ROUTE_INFO__ETCHER_QUAD(){};
	
	// ...
	virtual int Upload__FILE(const CString& path) = 0;
	virtual int Clear__MEM() = 0;
	
	virtual int Get__ROUTE_SERIAL_STEP_SIZE() = 0;
	virtual int Get__ROUTE_PARALLEL_PATH_SIZE(const int serial_step_index) = 0;
	
	virtual int Get__PMC_INFO(const int serial_step_index, 
		                      const int parallel_path_index, 
							  CDS__ROUTE_PMC_INFO& pmc_info) = 0;

	virtual int Check__FILE(const CString& path) = 0;

	// ...
	virtual double Get__Cooling_Time() = 0;
	virtual double Get__Preheat_Time() = 0;

	// ...
	virtual int Get__PMC_LIST_OF_FIRST_STEP(CUIntArray& l_pmc_id, 
		                                    CStringArray& l_pmc_rcp) = 0;

	virtual CString Get__VISION_RECIPE_NAME() = 0;
	
	// ...
	virtual int	Get__POSTCLN_SERIAL_STEP_SIZE() = 0;
	virtual int	Get__POSTCLN_PARALLEL_PATH_SIZE( const int nStepIdx ) = 0;

	virtual int Get__POST_CLN_INFO(const int _nSCnt,
		                           const int _nPCnt, 
								   CDS__POST_CLN_INFO& p_cln_info) = 0;

	virtual CString Get__CleanLL1_RecipeName() = 0;
	virtual CString Get__CleanLL2_RecipeName() = 0;
};

class SCI__FILE_ROUTE_CTRL
{
public:
	virtual ~SCI__FILE_ROUTE_CTRL(){};

	// ...
	virtual int Create__FILE(const CString& path) = 0;
	virtual int Close__FILE() = 0;

	virtual int Save__FILE() = 0;

	virtual int Delete__FILE(const CString& path) = 0;
	virtual int Delete__ALL_FILE(const CString& dir) = 0;

	virtual int Check__FILE(const CString& path) = 0;

	virtual int Add__PATH(const int pm_id,
						  const CString& pm_recipe) = 0;
	virtual int End__STEP() = 0;

	virtual int Rename__FILE(const CString& src_path,
							 const CString& trg_path) = 0;
	virtual int Copy__FILE(const CString& src_path,
						   const CString& trg_path)   = 0;

	// ...
	virtual int Clear__POLISHER_ALL_INFO() = 0;

	virtual int Add__POLISHER_HEAD_USE(const CStringArray& l_head_use) = 0;
	virtual int Add__POLISHER_PARALLEL_MODE(const int mode_flag) = 0;
	virtual int Add__POLISHER_RECIPE_INFO(const CUIntArray& l_stage_id,
		                                  const CStringArray& l_head_recipe,
										  const CStringArray& l_conditioner_recipe,
										  const CStringArray& l_sub_recipe) = 0;

	//
	virtual int Clear__CLEANER_ALL_INFO() = 0;

	virtual int Add__CLEANER_RECIPE_INFO(const CUIntArray& l_stage_id,
		                                 const CStringArray& l_stage_reccipe) = 0;

	//
	virtual int Clear__MEASUREMENT_ALL_INFO() = 0;

	virtual int Add__PRE_MEASUREMENT_RECIPE_INFO(const CString& recipe_name) = 0;
	virtual int Add__POST_MEASUREMENT_RECIPE_INFO(const CString& recipe_name) = 0;

	//
	virtual int Save_Buffer__POLISHER_And_CLEANER_And_MEASUREMENT() = 0;
};


// ...
class SCI__MATERIAL_LOG
{
public:
	virtual ~SCI__MATERIAL_LOG(){};

	// ...
	virtual int Set__DIR_ROOT(const CString& dir_root) = 0;
	virtual int Set__DATE_LIMIT(const int limit)  = 0;


	virtual int Start__LOG(const CString& lotid,
						   const CString& portid) = 0;

	virtual int End__LOG(const CString& lotid,
						 const CString& portid)   = 0;

	// ...
	// arm_type 
	//		0 : lower-arm
	//		1 : upper-arm
	// action
	//		0 : picking
	//      1 : pick
	//		2 : placing
	//      3 : place
	// module
	//		1 ~ 6 : PM1 ~ PM6
	//	   11 : AL
	//     21 : CL
	//     31 ~ 40 : PORT1 ~ PORT10
	
	virtual int Write__LOG(const int arm_type,
						   const int action,
						   const int module,
						   const CString& material,
						   const CString& lotid,
						   const CString& recipe) = 0;
};


class SCI__LOT_SUMMARY
{
public:
	virtual ~SCI__LOT_SUMMARY(){};

	// ...
	virtual int Set__DIR_ROOT(const CString& dir_root) = 0;
	virtual int Set__DATE_LIMIT(const int limit) = 0;

	virtual int Write__LOT_LOG(const CString& lotid,
						   const CString& portid) = 0;
	virtual int End__LOT_LOG(const CString& lotid,
						     const CString& portid) = 0;

	virtual int Write__SLOT_LOG(const CString& lotid,
								const CString& portid,
								const int slot,
							    const CString& module,
								const CString& recipeid,
								const CString& log) = 0;
	virtual int End__SLOT_LOG(const CString& lotid,
							  const CString& portid,
							  const int slot) = 0;

	virtual int Set__MULTI_SLOT() = 0;
	virtual int Clear__LOT_LOG(const CString& lotid,
							   const CString& portid) = 0;

	virtual int Alarm_Post__LOT_SLOT(const CString& lotid,
									 const CString& portid,
									 const int slot,
								     const int alarmid,
									 const CString& prcid) = 0;
	virtual int Alarm_Clear__LOT_SLOT(const CString& lotid,
									  const CString& portid,
									  const int slot,
									  const int alarmid) = 0;

	// ...
	virtual int Write__LOT_LOG_EX(const CString& lotid,
						          const CString& portid,
								  const CString& user_id,
								  const CString& user_level) = 0;

};


// ...
#define  SCH_DB__LP_LIMIT				5
#define  SCH_DB__PM_LIMIT				6

#define  SCH_DB__PM_SLOT_LIMIT			3	
#define  SCH_DB__LP_SLOT_LIMIT			26

#define  SCH_DB__LLx_LIMIT				4
#define  SCH_DB__LLx_SLOT_LIMIT			2

#define  SCH_DB__ROUTE_MODULE_LIMIT		SCH_DB__PM_LIMIT+SCH_DB__LLx_LIMIT


class CDB_MATERIAL_ROUTE_INFO
{
public:
	CDB_MATERIAL_ROUTE_INFO()
	{
		int i;
		for(i=0;i<SCH_DB__PM_LIMIT;i++)	
			PM_MODULE[i] = "";
	}

	CString PM_MODULE[SCH_DB__PM_LIMIT];
};

class CDB_MATERIAL_ITEM
{
public:
	int			 PORT;
	int			 SLOT;
	CString		 LOTID;
	CString		 PPID;
	CString		 MATERIAL_ID;
	CString		 MATERIAL_TYPE;
	CString		 PRC_ID;

	CString		 PM_MODULE[SCH_DB__PM_LIMIT];
	CString		 PM_RECIPE[SCH_DB__PM_LIMIT];

	int			 STEP_COUNT;
	int			 STEP_LIMIT;
	CStringArray DB_MODULE[SCH_DB__ROUTE_MODULE_LIMIT];	 // MODULE : LBX -> PMC -> LBX
	CStringArray DB_RECIPE[SCH_DB__ROUTE_MODULE_LIMIT];	 // RECIPE : LBX -> PMC -> LBX

	int			 iPREHEAT_TIME;
	int			 iCOOLING_TIME;

	CString      VISION_RECIPE;
	int			 iVISION_CONFIG_MODE;
};

class CDB_MATERIAL : public CDB_MATERIAL_ITEM
{
public:
	CDB_MATERIAL()
	{
		mSource_LP = "";
		mTarget_LP = "";

		mCurrent_Pos  = "";
		mMoving_Pos   = "";
		mMoving_Slot  = -1;
		mNext_Pos     = "";
		mStatus       = "";
		mVisit_Module = "";
		mBusy         = -1;
		mPort_End     = -1;
		mPort_Abort   = -1;
		mPort_Pause   = -1;
	}

	// ...
	CString mSource_LP;
	CString mTarget_LP;

	CString mCurrent_Pos;
	CString mMoving_Pos;
	int     mMoving_Slot;
	CString mNext_Pos;
	CString mStatus;
	CString mVisit_Module;
	int     mBusy;
	int     mPort_End;
	int     mPort_Abort;
	int     mPort_Pause;
};

class CDB_MATERIAL_EX : public CDB_MATERIAL
{
public:
	CDB_MATERIAL_EX()
	{
		sIO_MODE = "DUMP";

		iTRG_PORT = -1;
		iTRG_SLOT = -1;
	}

	// ...	
	CString sIO_MODE;

	int iTRG_PORT;
	int iTRG_SLOT;
};


class SCI__SCHEDULER_DB_CTRL
{
public:
	virtual ~SCI__SCHEDULER_DB_CTRL(){};

	// ...
	virtual int  SCH__Load_DB(const CDB_MATERIAL& db_material) = 0;

	virtual int  SCH__Loop_Start() = 0;
	virtual int  SCH__Loop_Exe(CDB_MATERIAL& db_material) = 0;
	virtual int  SCH__Loop_Exe(const int& port,
							   CDB_MATERIAL& db_material) = 0;
	virtual int  SCH__Loop_Next() = 0;

	// ...
	virtual int  Check_Serial_Step_In_PMC(const CDB_MATERIAL& al_info) = 0;
	virtual int  Check_Route_Recipe_In_TMC(const int pmc_index) = 0;
	virtual int  Check_Port_In_TMC(const int port_index) = 0;
	virtual int  Check_PM_Module_In_DB(const int pmc_index) = 0;
	
	virtual int  Pick_From_Module(const CString& arm,
								  const CString& module,
								  const int pmc_flag) = 0; 
	virtual int  Place_To_Module(const CString& arm,
								 const CString& module,
								 const int pmc_flag) = 0;

	virtual int  Set_Next_Module(const CString& module,
								 const CString& next_module) = 0;
	virtual int  Clear_Material(const int& port,
								const int& slot) = 0;
	virtual int  Clear_Port(const int& port) = 0;
	virtual int  Clear_All() = 0;
	virtual int  Set_Status(const CString& module,
							const CString& status) = 0;
	virtual int  Get_Status(const CString& module,
							CString& status) = 0;
	virtual int  Set_Visit(const int& port,
						   const int& slot,
						   const CString& module) = 0;
	virtual int  Set_Busy(const int& port,
						  const int& slot,
						  const CString& moving_module,
						  const int& moving_slot) = 0;
	virtual int  Set_Complete(const int& port,
							  const int& slot) = 0;
	virtual int  Get_Info(const CString& module,
						  CDB_MATERIAL& db_material) = 0;
	virtual int  Get_Info(int portid,int slotid,
						  CDB_MATERIAL& db_material) = 0;
	virtual int  Get_DB_Size() = 0;
	virtual int  Get_First_Slot_Mapped(const int& port) = 0;
	virtual int  Get_Port_Size(const int& port) = 0;
	virtual int  Set_Port_End(const int& port) = 0;
	virtual int  Set_Port_End(const int& port,
							  const int& slot) = 0;
	virtual int  Set_Port_Abort() = 0;
	virtual int  Set_Port_Abort(const int& port) = 0;
	virtual int  Set_Port_Pause(const int& port) = 0;
	virtual int  Set_Port_Resume(const int& port) = 0;
	virtual int  Is_Port_End(const int& port) = 0;


	virtual int  Is_Slot_To_Process(const int& port) = 0;
	virtual int  Is_Slot_To_Process() = 0;
	virtual int  Is_Slot_To_Process_And_Less_Than_Pick_Count(const int pick_count) = 0;
	
	virtual int  Is_Material_In_Module(const CString& module) = 0;
	virtual int  Get_Material_Status_In_Module(const CString& module,CString& material_sts) = 0;


	virtual int  Init_Order() = 0;
	virtual int  Push_Order(const int& port) = 0;
	virtual int  Pop_Order() = 0;
	virtual int  Pop_Order(const int db_index) = 0;
	virtual int  Pop_Order_With_PortID(const int db_index) = 0;
	virtual int  Is_Next_Order(const int s_port,int& port) = 0;
	
	
	// RECIPE - CONTROL ...
	virtual int  RECIPE__Go_Next_Step(const int& port,
									  const int& slot) = 0;
	virtual int  RECIPE__Can_Next_Step(const int& port,
									   const int& slot) = 0;
	virtual int  RECIPE__Can_Next_Step(const CString& module) = 0;
	virtual int  RECIPE__Get_Next_Step_Info(const int& port,
											const int& slot,
											CDB_MATERIAL& db_material) = 0;
	virtual int  RECIPE__Get_Next_Step_Info(const CString& module,
											CDB_MATERIAL& db_material) = 0;
	virtual int  RECIPE__Get_Route_Info_From_Port(const int port,
												  CDB_MATERIAL_ROUTE_INFO& db_route) = 0;
	virtual int  RECIPE__Get_Route_Info_From_Port_Mapped(const int port,
														 CDB_MATERIAL_ROUTE_INFO& db_route) = 0;

	// ...
	virtual int  Count__MATERIAL_To_PMC_In_SYSTEM(const int& pm_index) = 0;

	virtual int  Is_NEXT_PPID__EQUAL_To(const CString& module) = 0;
	virtual int  Is_NEXT_MODULE_Of_MATERIAL(const CString& module,
											const int& pmc_index) = 0;

	// ...
	virtual int  Process_Start__CEID(const CString& pmc_module,
									 const CString& recipe) = 0;
	
	virtual int  Process_End__CEID(const CString& pmc_module) = 0;

	// ...
	virtual int  Can_Pick_Slot_To_Process() = 0;

	virtual int  Set__DB_BUFFER() = 0;

	virtual int  Check_DB(const int port,
						  CString& msg) = 0;

	virtual int  Count__MATERIAL_To_PMC_In_LBx(const CString& ppid) = 0;

	// ...
	virtual int  SCH__Load_DB__EX(const CDB_MATERIAL_EX& db_material) = 0;

	virtual int  SCH__Loop_Exe__EX(CDB_MATERIAL_EX& db_material) = 0;
	virtual int  SCH__Loop_Exe__EX(const int& port,
								   CDB_MATERIAL_EX& db_material) = 0;

	// ...
	virtual int  Get_First_DB_Mapped(const int& port) = 0;

	virtual int  Get__LP_MATERIAL(CDB_MATERIAL& db_material) = 0;
	virtual int  Check__Next_Route_Recipe(const int port_id,const int slot_id) = 0;

	virtual int  Check_DB(CString& msg) = 0;

	virtual int  Process_Start__CEID(const int port_id,const int slot_id,
									 const CString& pm_module,const CString& recipe) = 0;

	// ...
	virtual int  Is__Material_In_System() = 0;

	virtual int  Set__GoTo_Module(const CString& cur_pos,
								  const CString& module) = 0;
	virtual int  Get__GoTo_Module(const CString& cur_pos,
								  CString& module) = 0;

	// ...
	virtual int  SCH__Get_DB__At_FIRST_POS(CDB_MATERIAL& db_material) = 0;
	virtual int  SCH__Load_DB__At_FIRST_POS(const CDB_MATERIAL& db_material) = 0;
	virtual int  SCH__Get_DB__At_FIRST_MAPPED_POS(CDB_MATERIAL& db_material) = 0;
};


// ...
class SCI__VARIABLE_CTRL
{
public:
	virtual ~SCI__VARIABLE_CTRL(){};

	// ...
	virtual int Get__DATA(const CString& obj_name,const CString& var_name,CString& ch_data) = 0;
	virtual int Get__DATA(const CString& ch_name,CString& ch_data) = 0;

	virtual int Set__DATA(const CString& obj_name,const CString& var_name,const CString& ch_data) = 0;
	virtual int Set__DATA(const CString& ch_name,const CString& ch_data) = 0;

	// ...
	virtual int Is_Exist__DATA(const CString& obj_name,const CString& var_name,const CString& ch_data) = 0;
	virtual int Is_Exist__DATA(const CString& ch_name,const CString& ch_data) = 0;
};

class SCI__ANALOG_CHANNEL
{
public:
	virtual ~SCI__ANALOG_CHANNEL(){};

	// ...
	virtual int Register__CHANNEL_NAME(const CString& ch_name) = 0;
	virtual int Register__ABORT_CHANNEL(const CString& ch_abort) = 0;

	virtual int Set__DATA(const CString& data) = 0;
	virtual int Set__DATA(const double value) = 0;

	virtual int Get__DATA(CString& data) = 0;
	virtual int Get__DATA(double& data)  = 0;

	virtual int When__MORE_THAN(const double value) = 0;
	virtual int When__MORE_THAN(const double value,const double sec) = 0;
	virtual int When__LESS_THAN(const double value) = 0;
	virtual int When__LESS_THAN(const double value,const double sec) = 0;

	// ...	
	virtual int Get__CHANNEL_NAME(CString& ch_name) = 0;
	virtual int Get__ABORT_CHANNEL(CString& ch_abort) = 0;

	virtual int Check__CHANNEL_NAME(const CString& ch_name) = 0;

	// ...
	virtual int Check__MORE_THAN(const double value) = 0;
	virtual int Check__LESS_THAN(const double value) = 0;

	// ...
	virtual double Get__VALUE() = 0;
};
class SCI__DIGITAL_CHANNEL
{
public:
	virtual ~SCI__DIGITAL_CHANNEL(){};

	// ...
	virtual int Register__CHANNEL_NAME(const CString& ch_name) = 0;
	virtual int Register__ABORT_CHANNEL(const CString& ch_abort) = 0;
	
	virtual int Set__DATA(const CString& data) = 0;
	virtual int Get__DATA(CString& data) = 0;
	
	virtual int Check__DATA(const CString& data) = 0;
	virtual int Check__DATA(const CString& data1,const CString& data2) = 0;
	virtual int Check__DATA(const CStringArray& l_data) = 0;
	
	virtual int When__DATA(const CString& data) = 0;
	virtual int When__DATA(const CString& data1,const CString& data2) = 0;
	virtual int When__DATA(const CStringArray& l_data) = 0;

	virtual int When__DATA(const CString& data,const double sec) = 0;
	virtual int When__DATA(const CStringArray& l_data,const double sec) = 0;
	
	virtual int When__NOT_DATA(const CString& data) = 0;
	virtual int When__NOT_DATA(const CString& data,const double sec) = 0;

	virtual int Wait__CTRL() = 0;
	virtual int Wait__CTRL(const double sec) = 0;
	virtual int Wait__CTRL(const CString& data1,const CString& data2) = 0;

	// ...
	virtual int Register__ALARM_ID(const int alarm_id) = 0;
									
	virtual int Popup__MESSAGE_BOX(const CString& title,
								   const CString& message,
								   const CString& option,
								   CString& act_result) = 0;
	virtual int Popup__MESSAGE_BOX(const CString& title,
								   const CString& message,
								   const CStringArray& l_option,
								   CString& act_result) = 0;
									
	virtual int Popup__ALARM_BOX(const CString& title,
								 const CString& message,
								 const CString& option,
								 CString& act_result) = 0;
	virtual int Popup__ALARM_BOX(const CString& title,
								 const CString& message,
								 const CStringArray& l_option,
								 CString& act_result) = 0;

	// ...
	virtual int Get__CHANNEL_NAME(CString& ch_name) = 0;
	virtual int Get__ABORT_CHANNEL(CString& ch_abort) = 0;

	virtual int Check__CHANNEL_NAME(const CString& ch_name) = 0;

	// ...
	virtual int Get__IO_INFO(CString& md_id,CString& ch_id, CString& cmmd1,CString& cmmd2,CString& cmmd3) = 0;
};
class SCI__STRING_CHANNEL
{
public:
	virtual ~SCI__STRING_CHANNEL(){};

	// ...
	virtual int Register__CHANNEL_NAME(const CString& ch_name) = 0;
	virtual int Register__ABORT_CHANNEL(const CString& ch_abort) = 0;

	virtual int Set__DATA(const CString& data)  = 0;
	virtual int Get__DATA(CString& data) = 0;
	
	virtual int Check__DATA(const CString& data) = 0;
	virtual int Check__DATA(const CString& data1,const CString& data2) = 0;
	
	virtual int When__DATA(const CString& data) = 0;
	virtual int When__DATA(const CString& data1,const CString& data2) = 0;
	virtual int When__DATA(const CStringArray& l_data) = 0;

	virtual int When__DATA(const CString& data,const double sec) = 0;
	virtual int When__DATA(const CStringArray& l_data,const double sec) = 0;

	virtual int When__NOT_DATA(const CString& data) = 0;
	virtual int When__NOT_DATA(const CString& data,const double sec) = 0;

	// ...
	virtual int Get__CHANNEL_NAME(CString& ch_name) = 0;
	virtual int Get__ABORT_CHANNEL(CString& ch_abort) = 0;

	virtual int Check__CHANNEL_NAME(const CString& ch_name) = 0;
};


// ...
class SCI__SEQ_INFO
{
public:
	virtual ~SCI__SEQ_INFO(){};

	// ...
	virtual int Get__DIR_ROOT(CString& dir) = 0;
	virtual int Get__DIR_INCLUDE_FILE(CString& dir) = 0;
	virtual int Get__DIR_CONFIG(CString& dir) = 0;
	virtual int Get__DIR_USER_LOG(CString& dir) = 0;

	virtual int Get__DIR_PROCESS(CString& dir) = 0;
	virtual int Get__DIR_PROCESS_ROUTE(CString& dir) = 0;
	virtual int Get__DIR_PROCESS_CASSETTE(CString& dir) = 0;
	virtual int Get__DIR_PROCESS_JOB(CString& dir) = 0;

	virtual int Get__DIR_PMx_PROCESS(const int pm_id,CString& path) = 0;

	// ...	
	virtual int Get__SEQ_INFO(CString& device_name,int& seq_id) = 0;

	virtual int Create__DIR(const CString& dir) = 0;

	// ...
	virtual int Is__SIMULATION_MODE() = 0;
	virtual int Is__RUN_MODE() = 0;

	// ...
	virtual int Get__DIR_USER_LOG_OBJECT(CString& dir) = 0;

	virtual int Convert__STR_TO_DAY(const CString& str_day,
									int& i_year,int& i_mon,int& i_day) = 0;

	virtual int Get__DAY(int& i_year,int& i_mon,int& i_day) = 0;

	virtual int Get__DAY_COUNT(const int s_year,const int s_mon,const int s_day,
							   const int t_year,const int t_mon,const int t_day) = 0;

	// ...
	virtual int Get__TIME(int& i_hour,int& i_min,int& i_sec,int& i_msec) = 0;
	virtual CString Get__DATE_TIME_STRING() = 0;

	// ...
	virtual int  Enable__System_Log() = 0;
	virtual int  Disable__System_Log() = 0;
	
	virtual int  Set__System_Log_Backup_Day(const int backup_day) = 0;

	// ...
	virtual int  Get__Thread_All_List_MSG(CString& db_msg) = 0;
	virtual int  Get__File_Log_All_List_MSG(CString& db_msg) = 0;

	// ...
	virtual CString Get__DATE_TIME__YYYYMMDDhhmmss() = 0;
	virtual CString Get__DATE_TIME__YYYYMMDDhhmmss_msec() = 0;

	// ...
	virtual int Get__IP_PORT_INFO_OF_SEQ_ID(const int seq_id, CString& seq_ip,int& seq_port) = 0;

	// ...
	virtual int Get__LOG_DB_SIZE() = 0;
};


// ...
class CDB__JOB_INFO
{
public:
	int PORTID;

	int SLOT_LIMIT;
	int SLOT_LIST[30];

	CString LOTID;
	CString PPID;
};

class SCI__JOB_CTRL
{
public:
	virtual ~SCI__JOB_CTRL(){};

	// ...
	virtual int Clear() = 0;
	
	virtual int Upload_Fab_Table(const CString& dir) = 0;
	virtual int Upload_Fab(const CString& dir) = 0;
	
	virtual int Upload_Job(const CString& dir,
						   const CString& port,
						   const CString& file) = 0;
	virtual int Upload_Route(const CString& dir,
							 const CString& file,
							 int slot_index) = 0;

	virtual int Copy_DB(const int index,
						CDB_MATERIAL_ITEM& db_material) = 0;

	virtual	int Check() = 0;
	virtual int Check_PM(const CString& word) = 0;

	virtual int Make_Fab(const CString& dir,
						 const CString& file_name,
						 const CDB__JOB_INFO& db_info) = 0;


	virtual int  Get_Fab__Dummy_Only_Flag() = 0;
	virtual int  Get_Fab__LP_Active_Limit() = 0;
	virtual int  Get_Fab__LP_Active_Status(const int lp_index) = 0;

	virtual void Get_Fab__Job_Name(CString& job_name) = 0;
	virtual void Get_Fab__LP_LotID(const int lp_index,
								   CString& lotid) = 0;

	virtual int  Get_Fab__Dummy_Slot_Limit() = 0;
	virtual int  Get_Fab__Dummy_Slot_Status(const int slot_index) = 0;
	virtual void Get_Fab__Dummy_PPID(CString& ppid) = 0;
	virtual void Get_Fab__Process_PPID(CString& ppid) = 0;


	virtual int  Get__TRG_PTN(CString& trg_ptn) = 0;
	virtual int  Get__IO_MODE(CString& io_mode) = 0;

	virtual int  Get__SLOT_TO_SLOT__SIZE() = 0;
	virtual int  Get__SLOT_TO_SLOT__INFO(const int src_slot,
										 int& trg_ptn,
										 int& trg_slot) = 0;
	virtual int  Get__MTRLOUTSPEC_INFO(CUIntArray& l_src_slot,
									   CUIntArray& l_trg_ptn,
									   CUIntArray& l_trg_slot) = 0;
};


// ...
class SCI__MODULE_INFO
{
public:
	virtual ~SCI__MODULE_INFO(){};

	// ...
	virtual int Is__ONLINE(const int seq_id) = 0;
};


// ...
class SCI__PM_DATALOG
{
public:
	virtual ~SCI__PM_DATALOG(){};

	// ...
	virtual int Set__CYCLE_LIMIT(const int cycle_limit) = 0;

	virtual int Start__DATALOG(const CString& path) = 0;
	virtual int Start__DATALOG(const CString& path,const int module_id) = 0;

	virtual int Stop__DATALOG() = 0;
	virtual int Stop__DATALOG(const int module_id) = 0;

	virtual int Start__STEP(const int module_id,const int step_id) = 0;
	virtual int End__STEP(const int module_id,const int step_id)   = 0;
	virtual int Abort__STEP(const int module_id,const int step_id) = 0;

	virtual int Pause__DATALOG(const int module_id) = 0;
	virtual int Resume__DATALOG(const int module_id) = 0;

	virtual int Write__ALL_ITEM(const CString& path) = 0;
	virtual int Start__DATALOG_TIME(const CString& path,const double log_sec) = 0;

	// ...
	virtual int Backup__FILE(const CString& src_path,const CString& trg_path) = 0;
	virtual int Make__FILE(const CString& log_path,const CString& log_msg) = 0;

	// ...
	virtual int Start__MULTI_DATALOG(const CString& path,const int module_id) = 0;

	// ...
	virtual int Start__DATALOG_WITH_MSG(const CString& path,const int module_id,const CString& log_msg) = 0;
	virtual int Start__MULTI_DATALOG_WITH_MSG(const CString& path,const int module_id,const CString& log_msg) = 0;
};

class SCI__PM_CSV_LOG
{
public:
	virtual ~SCI__PM_CSV_LOG(){};

	// ...
	virtual int Set__CYCLE_LIMIT(const int cycle_limit) = 0;

	virtual int Start__DATALOG(const CString& path) = 0;
	virtual int Start__DATALOG(const CString& path,const int module_id) = 0;

	virtual int Stop__DATALOG() = 0;
	virtual int Stop__DATALOG(const int module_id) = 0;

	virtual int Start__STEP(const int module_id,const int step_id) = 0;
	virtual int End__STEP(const int module_id,const int step_id)   = 0;
	virtual int Abort__STEP(const int module_id,const int step_id) = 0;

	virtual int Pause__DATALOG(const int module_id) = 0;
	virtual int Resume__DATALOG(const int module_id) = 0;

	virtual int Write__ALL_ITEM(const CString& path) = 0;

	// ...
	virtual int Backup__FILE(const CString& src_path,const CString& trg_path) = 0;
	virtual int Make__FILE(const CString& log_path,const CString& log_msg) = 0;
};


// ...
class SCI__CONDITION
{
public:
	virtual ~SCI__CONDITION(){};

	// ...
	virtual int Load__CONDITION(const CString& obj_name,
								const CString& var_name,
								const CString& cnd_para,
								const CString& ch_data) = 0;
	virtual int Load__CONDITION(const CString& obj_name,
								const CString& var_name,
								const CString& cnd_para,
								const double&  ch_data) = 0;

	virtual int Load__CONDITION(const CString& channel,
								const CString& cnd_para,
								const CString& ch_data) = 0;
	virtual int Load__CONDITION(const CString& channel,
								const CString& cnd_para,
								const double&  ch_data) = 0;

	virtual int Register__CHANNEL(const CString& obj_name,
								  const CString& var_name) = 0;
	virtual int Register__CHANNEL(const CString& channel) = 0;

	virtual int Load__OR(SCI__CONDITION*  p_con) = 0;
	virtual int Load__AND(SCI__CONDITION* p_con) = 0;

	virtual int Load__OR(const int con_size, SCI__CONDITION** p_con) = 0;
	virtual int Load__AND(const int con_size,SCI__CONDITION** p_con) = 0;

	virtual int Check__CONDITION() = 0;
	virtual int Init__CONDITION()  = 0;

	virtual int Start__CHECK() = 0;
	virtual int Stop__CHECK()  = 0;

	virtual int Clear__Sub_Condition_Memory() = 0;
};


class SCI__DEVICENET_INFO
{
public:
	virtual ~SCI__DEVICENET_INFO(){};

	// ...
	virtual int Get__TOTAL_INFO(int& total_in_byte,
								int& total_out_byte,
								int& total_front_offset_bit,
								int& total_back_offset_bit) = 0;

	virtual int Get__HW_ID_INFO(const int hw_id,
								int& total_in_byte,
								int& total_out_byte,
								int& total_front_offset_bit,
								int& total_back_offset_bit) = 0;

};


class SCI__CHANNEL_INFO
{
public:
	virtual ~SCI__CHANNEL_INFO(){};

	// ...
	virtual int Get__ANALOG_INFO(const CString& ch_name,
								 double& min_vaule,
								 double& max_vaule,
								 int& dec) = 0;

	virtual int Get__DIGITAL_INFO(const CString& ch_name,
								  CStringArray& l_item) = 0;

	virtual int Get__DESCRIPTOR_INFO(const CString& obj_name,
									 const CString& descriptor_name,
								     CStringArray& l_item) = 0;
};


// ...
#define DEF_QUERY__CPU_PERCENT				"CPU.PERCENT"
#define DEF_QUERY__HW_KEY_TYPE_CHECK		"HW.KEY.TYPE.CHECK"
#define DEF_QUERY__SYS_ERROR				"SYS.ERROR"
#define DEF_QUERY__ALARM_POST_SIZE			"ALARM.POST.SIZE"
#define DEF_QUERY__FA_SERVER_UNIT_SIZE      "FA_SERVER.UNIT.SIZE"


class SCI__SEQ_CORE__QUERY
{
public:
	virtual ~SCI__SEQ_CORE__QUERY(){};

	// ...
	virtual double Get__VERSION() = 0;

	virtual int Get__QUERY(const CString& in_query,
						   CString& out_answer) = 0;
	virtual int Get__QUERY_LIST(const CString& in_query,
							    CStringArray& l_out_answer) = 0;

	virtual int Get__MULTI_QUERY(const CString& main_query,
								 const CString& sub_query,
								 CString& out_answer) = 0;
	virtual int Get__MULTI_QUERY_LIST(const CString& main_query,
									  const CString& sub_query,
								      CStringArray& l_out_answer) = 0;
};

class SCI__DB_CTRL
{
public:
	virtual ~SCI__DB_CTRL(){};

	// ...
	virtual int Create__DB_NAME(const CString& db_name,const int db_size) = 0;
	virtual int Link__DB_NAME(const CString& db_name) = 0;

	virtual int Set__INFO(const CString& title_name,const CString& item_name,const CString& item_data) = 0;
	virtual int Get__INFO(const CString& title_name,const CString& item_name,CString& item_data) = 0;

	virtual int Get__DB_LIST(CStringArray& l_db_name) = 0;
	virtual int Get__TITLE_LIST(const CString& db_name,CStringArray& l_title_name) = 0;
	virtual int Get__ITEM_LIST(const CString& db_name,const CString& title_name,CStringArray& l_item_name,CStringArray& l_item_data) = 0;
};


// ...
class SCI__SYSTEM_CTRL
{
public:
	virtual ~SCI__SYSTEM_CTRL(){};

	// ...
	virtual int Get__ALL_OBJECT_LIST(CStringArray& l__obj_name) = 0;
	virtual int Get__ALL_OBJECT_LIST(CStringArray& l__obj_name, CStringArray& l__obj_sts) = 0;

	virtual int Get__OBJECT_COUNT_IN_RUN_STATE() = 0;
	virtual int Get__OBJECT_LIST_IN_RUN_STATE(CStringArray& l__obj_name) = 0;

	virtual int Abort__OBJECT_IN_RUN_STATE(const bool active_all, const CString& obj_name, CStringArray& l__abort_obj) = 0;
};
