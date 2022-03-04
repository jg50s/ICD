#pragma once


class CI_RECIPE_CONFIG
{
public:
	virtual int Init() = 0;

	virtual int Register_Digital(const CString& channel) = 0;
	virtual int Register_String(const CString& channel)  = 0;
	virtual int Register_Analog(const CString& channel)  = 0;

	virtual int Get_Item(const CString& channel,CString& data) = 0;
	virtual int Save_Item(const CString& channel,const CString& data) = 0;
	virtual int Get_Item_Info(const int& index,
							  CString& channel,
							  CString& type,
							  CString& data) = 0;
};

class CI_DRAW
{
public:
	virtual int Ellipse(HDC hdc,HDC hdc_back,POINT st,POINT et,
					    COLORREF tcolor = RGB(0,0,0),
						COLORREF bcolor = RGB(255,255,255),
						int		 thickness = 1) = 0;
	virtual int Rectangle(HDC hdc,HDC hdc_back,POINT st,POINT et,
						  COLORREF tcolor = RGB(0,0,0),
						  COLORREF bcolor = RGB(255,255,255),
						  int	   thickness = 1) = 0;
	virtual int Polygon(HDC hdc,HDC hdc_back,POINT *pt,int limit,
						COLORREF tcolor = RGB(0,0,0),
						COLORREF bcolor = RGB(255,255,255),
						int      thickness = 1) = 0;
	virtual int TextLeft(HDC hdc,HDC hdc_back,
						 CString  text,
						 POINT    pt,
						 LOGFONT  fontlog,
						 COLORREF tcolor = RGB(0,0,0),
						 COLORREF bcolor = RGB(255,255,255)) = 0;
	virtual int TextCenter(HDC hdc,HDC hdc_back,
						   CString  text,
						   POINT    pt,
						   LOGFONT  fontlog,
						   COLORREF tcolor = RGB(0,0,0),
						   COLORREF bcolor = RGB(255,255,255)) = 0;
	virtual int TextRight(HDC hdc,HDC hdc_back,
						  CString  text,
						  POINT    pt,
						  LOGFONT  fontlog,
						  COLORREF tcolor = RGB(0,0,0),
						  COLORREF bcolor = RGB(255,255,255)) = 0;
	virtual int GetFont(CString fontname,LOGFONT *fontlog) = 0;
	virtual int Line(HDC hdc,HDC hdc_back,
					 POINT st,POINT et,
				 	 COLORREF color = RGB(0,0,0),
					 int thickness = 1) = 0;
	virtual int LineEx(HDC hdc,HDC hdc_back,
					 POINT st,POINT et,
					 int mode = PS_SOLID,
					 COLORREF color = RGB(0,0,0),
					 int thickness = 1) = 0;

	///////////////////////////////////////////////////////////////////
	virtual int HDC_Ellipse(HDC hdc,POINT st,POINT et,
						COLORREF tcolor = RGB(0,0,0),
						COLORREF bcolor = RGB(255,255,255),
						int thickness = 1) = 0;
	virtual int HDC_Rectangle(HDC hdc,POINT st,POINT et,
						  COLORREF tcolor = RGB(0,0,0),
						  COLORREF bcolor = RGB(255,255,255),
						  int thickness = 1) = 0;
	virtual int HDC_Polygon(HDC hdc,POINT *pt,int limit,
					    COLORREF tcolor = RGB(0,0,0),
						COLORREF bcolor = RGB(255,255,255),
						int      thickness = 1) = 0;
	virtual int HDC_TextLeft(HDC hdc,
						 CString  text,
						 POINT    pt,
						 LOGFONT  fontlog,
						 COLORREF tcolor = RGB(0,0,0),
						 COLORREF bcolor = RGB(255,255,255)) = 0;
	virtual int HDC_TextCenter(HDC hdc,
						   CString  text,
						   POINT    pt,
						   LOGFONT  fontlog,
						   COLORREF tcolor = RGB(0,0,0),
						   COLORREF bcolor = RGB(255,255,255)) = 0;
	virtual int HDC_TextRight(HDC hdc,
						  CString  text,
						  POINT    pt,
						  LOGFONT  fontlog,
						  COLORREF tcolor = RGB(0,0,0),
						  COLORREF bcolor = RGB(255,255,255)) = 0;
	virtual int HDC_Line(HDC hdc,
					 POINT st,POINT et,
				 	 COLORREF color = RGB(0,0,0),
					 int thickness = 1) = 0;
	virtual int HDC_LineEx(HDC hdc,
					 POINT st,POINT et,
					 int mode = PS_SOLID,
					 COLORREF color = RGB(0,0,0),
					 int thickness = 1) = 0;

	virtual int HDC_Copy(HDC trg_hdc,HDC src_hdc,POINT st,POINT et) = 0;

	virtual int HDC_Copy(HDC trg_hdc,POINT trg_st,POINT trg_et,HDC src_hdc,POINT src_st,POINT src_et) = 0;
};

class CI_BMP
{
public:
	virtual int MaskColor(COLORREF color) = 0;
	virtual int MaskDisable() = 0;
	virtual int Load(HINSTANCE hinst,int bmpid,HDC hdc) = 0;
	virtual int Draw(HDC hdc,HDC hdc_back,HDC hdc_mem,POINT st,POINT et) = 0;
	virtual int BackgroundRestoreDisable() = 0;
	virtual int BackgroundRestoreEnable() = 0;

	virtual int SetPosition(const POINT& st,const POINT& et) = 0;
	virtual int CheckArea(const POINT& pt) = 0;
	virtual int Draw_HDC(HDC hdc,HDC hdc_back,HDC hdc_mem) = 0;
	virtual int Draw_HDC(HDC hdc) = 0;
	virtual int Draw_HWND(HWND hwnd) = 0;

	virtual void Destroy() = 0;
	virtual int  GetPosition(POINT& st,POINT& et) = 0;
	virtual int  Load_Ex(HINSTANCE hinst,int bmpid,HDC hdc) = 0;
};

class CI_BUTTON
{
public:
	virtual int SetFont(CString fontname,int width,int height) = 0;
	virtual int SetTextColor(COLORREF color) = 0;
	virtual int SetPosition(POINT st,POINT et) = 0;
	virtual int SetPressedColor(COLORREF color) = 0;
	virtual int SetReleasedColor(COLORREF color) = 0;
	virtual int SetThick(int thick) = 0;
	virtual int SetUpColor(COLORREF color) = 0;
	virtual int SetDownColor(COLORREF color) = 0;
	virtual int SetTitle(CString title) = 0;
	virtual int CheckArea(POINT pt) = 0;
	virtual int DrawPressed(HDC hdc,HDC hdc_back) = 0;
	virtual int DrawReleased(HDC hdc,HDC hdc_back) = 0;
	virtual int SetArrowLeft() = 0;
	virtual int SetArrowLeftDual() = 0;
	virtual int SetArrowRight() = 0;
	virtual int SetArrowRightDual() = 0;
	virtual int SetArrowUp() = 0;
	virtual int SetArrawUpDual() = 0;
	virtual int SetArrowDown() = 0;
	virtual int SetArrowDownDual() = 0;
	virtual int SetArrowColor(COLORREF color) = 0;
	virtual int SetLeftMode() = 0;
	virtual int SetRightMode() = 0;
	virtual int SetActive() = 0;
	virtual int SetInActive() = 0;
	virtual int SetTextColorPressed(COLORREF color) = 0;
	virtual int SetTextColorReleased(COLORREF color) = 0;
	virtual int GetPosition(POINT *st,POINT *et) = 0;
	virtual int GetTitle(CString& title) = 0;
	virtual int SetInActiveColor(COLORREF color) = 0;
	virtual int SetCheckBoxType() = 0;
	virtual int SetCheckStatus(int status) = 0;
	virtual int IsCheckStatus() = 0;

	virtual int HDC_DrawPressed(HDC hdc) = 0;
	virtual int HDC_DrawReleased(HDC hdc) = 0;

	virtual int IsActiveStatus() = 0;
	virtual int SetCheckBoxColor(COLORREF color) = 0;

	virtual int SetCenterMode() = 0;		// Default
};

class CI_UTILITY
{
public:
	//-------------------------------------------------
	virtual COLORREF GetColor(CString string) = 0;
	virtual COLORREF GetColor(CString string,int *r,int *g,int *b) = 0;

	virtual int Get_ChannelName(CString string,CString *channel) = 0;
	
	virtual int Popup_AnalogPad(CString channel,
							    CString data,
								CString min_max,
								CString *result) = 0;
	virtual int Popup_DigitalPad(CString channel,
								 CString data,
								 CString list,
								 CString *result) = 0;
	virtual int Popup_Keyboard(CString channel,
							   CString data,
							   CString *result) = 0;
	virtual int Popup_FileDialog(CString dir,CString file,CString ext,CString *path) = 0;
	virtual int Get_AlarmPost(CString *str_list) = 0;
	virtual int Get_Font(CString font,LOGFONT *logfont) = 0;

	virtual int Get_DirAlarmlog(CString *dir,CString *file) = 0;
	virtual int Alarm_Clear(CString module, CString type,
							CString time,   CString channel,
							CString title,  CString message,
							CString option, CString result) = 0;

	virtual int Popup_FileSearch(CString dir,CString ext,CString *file) = 0;
	virtual int Popup_Message(CString message) = 0;
	virtual int Popup_FileControl(CString dir,CString ext,CString *path) = 0;
	virtual int Popup_FileControl(CString dir,CString ext,CString *path,int length) = 0;
	virtual int Popup_DirSearch(CString dir,CString sub_dir,CString *result) = 0;

	virtual int Popup_FileControl_Ex(const CString& dir,const CString& ext,
									 CString *path,int length,
									 int password_mode,
									 const CString& recipe_exe,
									 const CString& password) = 0;
	//-------------------------------------------------

	//-------------------------------------------------
	virtual ~CI_UTILITY(){};
	//-------------------------------------------------
};

class CI_VSCROLLBAR
{
public:
	virtual int SetArrowColor(COLORREF color) = 0;
	virtual int SetDownColor(COLORREF color) = 0;
	virtual int SetUpColor(COLORREF color) = 0;
	virtual int SetPressedColor(COLORREF color) = 0;
	virtual int SetReleasedColot(COLORREF color) = 0;
	virtual int SetThick(int thick) = 0;
	virtual int SetPosition(POINT st,POINT et) = 0;
	virtual int Draw(HDC hdc,HDC hdc_back) = 0;
	virtual int CheckArea(POINT pt,HDC hdc,HDC hdc_back) = 0;
	virtual int SetSize(int size) = 0;
	virtual int SetRange(int range) = 0;
	virtual int SetThumbPos(int line) = 0;
	virtual int GetCurLine() = 0;
};

class CI_HSCROLLBAR
{
public:
	virtual int SetArrowColor(COLORREF color) = 0;
	virtual int SetDownColor(COLORREF color) = 0;
	virtual int SetUpColor(COLORREF color) = 0;
	virtual int SetPressedColor(COLORREF color) = 0;
	virtual int SetReleasedColot(COLORREF color) = 0;
	virtual int SetThick(int thick) = 0;
	virtual int SetPosition(POINT st,POINT et) = 0;
	virtual int Draw(HDC hdc,HDC hdc_back) = 0;
	virtual int CheckArea(POINT pt,HDC hdc,HDC hdc_back) = 0;
	virtual int SetSize(int size) = 0;
	virtual int SetRange(int range) = 0;
	virtual int SetThumbPos(int line) = 0;
	virtual int GetCurLine() = 0;
};

class CI_TABLE
{
public:
	virtual int SetPosition(int x,int y,int width,int height) = 0;
	virtual int Draw(HDC hdc,HDC hdc_back) = 0;
	virtual int CheckArea(POINT pt,HDC hdc,HDC hdc_back) = 0;
	virtual int AddString(CString data,HDC hdc,HDC hdc_back) = 0;
	virtual int Clear() = 0;
	virtual int SetBrushColorPressed(COLORREF color) = 0;
	virtual int SetBrushColorReleased(COLORREF color) = 0;
	virtual int SetTextColorPressed(COLORREF color) = 0;
	virtual int SetTextColorReleased(COLORREF color) = 0;
	virtual int EnableNumbering() = 0;
	virtual int DisableNumbering() = 0;
	virtual int SetItemList(int limit) = 0;
	virtual int ChangeString(int index,CString data,HDC hdc,HDC hdc_back) = 0;
	virtual int GetErrorMsg(CString *msg) = 0;
	virtual int SearchItem(CString data) = 0;
	virtual int GetData(int index,CString *data) = 0;
	virtual int GetCurData(CString *data) = 0;
	virtual int Draw_Table(HDC hdc,HDC hdc_back) = 0;	
	virtual int SetAllItem(CString data,HDC hdc,HDC hdc_back) = 0;
	virtual int SetFont(CString fontname,int width,int height) = 0;
	virtual int GetCurIndex() = 0;
};

class CI_DB_MDB 
{
public:
	CString	 mMDB_Path;
	CString	 mMDB_Table;
	int      mColumn_Limit;
	char     mTitle[100][200];
	char     mType[100][100];
	char     mProperty[100][100];
	char     mDisplay[100][100];

	int		 mHidden_Column_Limit;
	char     mHidden_Field[100][100];
	char     mHidden_Type[100][100];


	////////////////////////////////////////
	virtual int Upload() = 0;
	
	virtual int Save() = 0;
	virtual int Save_Item() = 0;
	virtual int Undo() = 0;
	virtual int Undo(int column,CString str_search) = 0;
	virtual int Delete_Item(int click_line) = 0;
	virtual int Insert_Item() = 0;
	virtual int Copy_Item(int click_line) = 0;
	
	virtual int Sort_Ascending(int column) = 0;
	virtual int Sort_Descending(int column) = 0;
	virtual int Search(int column,CString data) = 0;
	
	virtual int IsTotalRow() = 0;
	virtual int IsTotalColumn() = 0;
	
	virtual CString GetData(int column,int line) = 0;
	virtual int SetData(CString data,int column,int line) = 0;

	virtual int GetItem(CString search,CString ref_field,CString ref_data,CString &result) = 0;
	virtual int UpdateItem(CString item_name,CString item_data,CString ref_item,CString ref_data) = 0;

	virtual int Sort_Num_Ascending(int column) = 0;
	virtual int Sort_Num_Descending(int column) = 0;

	virtual int SetDataChange(int status) = 0;
	virtual int IsDataChange() = 0;

	virtual int SetBindData(int src,int trg) = 0;
	virtual int IsDuplicateData(int column) = 0;
	virtual int SetDataLimit(int limit) = 0;
	virtual int ClearColumnData(int column,CString clear_data) = 0;

	virtual int Clear_Item() = 0;
	////////////////////////////////////////
};

class CI_DB_RCP
{
public:
	CString		 mDir;
	CString		 mFile;
	CStringArray mList;

	virtual int Upload() = 0;
	virtual int SearchItem(CString file,int step,CString channel,CString &data) = 0;
	virtual int SortName() = 0;
};

class CI_TABLE_MDB 
{
public:
	CString	 mMDB_Path;
	CString	 mMDB_Table;
	COLORREF mNull_BColor;
	COLORREF mNull_TColor;
	COLORREF mTitle_BRColor;
	COLORREF mTitle_TRColor;	
	COLORREF mTitle_BPColor;
	COLORREF mTitle_TPColor;	
	COLORREF mItem_PressColor;
	COLORREF mItem_ClickColor;
	COLORREF mItem_BRColor;
	COLORREF mItem_TRColor;
	COLORREF mItem_BPColor;
	COLORREF mItem_TPColor;
	int      mColumn_Limit;
	char     mTitle[100][100];
	char     mField[100][100];
	char     mType[100][100];
	char     mFunction[100][100];
	char     mProperty[100][100];
	char     mRange[100][100];
	char     mDisplay[100][100];
	int      mWidth[100];

	int		 mHidden_Column_Limit;
	char     mHidden_Field[100][100];
	char     mHidden_Type[100][100];


	////////////////////////////////////////
	virtual int Init_Data() = 0;
	virtual int Init_Pos(POINT m_st,POINT m_et) = 0;
	virtual int Upload() = 0;
	
	virtual int Save(HDC hdc,HDC hdc_back) = 0;
	virtual int UndoOnly(HDC hdc,HDC hdc_back) = 0;
	virtual int Undo(HDC hdc,HDC hdc_back) = 0;
	virtual int Undo(int column,CString str_search,HDC hdc,HDC hdc_back) = 0;
	virtual int Delete_Item(HDC hdc,HDC hdc_back) = 0;
	virtual int Insert_Item(HDC hdc,HDC hdc_back) = 0;
	virtual int Copy_Item(HDC hdc,HDC hdc_back) = 0;
	
	virtual int Draw(HDC hdc,HDC hdc_back) = 0;
	virtual int CheckArea(POINT pt,HDC hdc,HDC hdc_back) = 0;
	
	virtual int SetFontName(CString fontname,int width,int height) = 0;
	
	virtual int Sort_Ascending(int column,HDC hdc,HDC hdc_back) = 0;
	virtual int Sort_Descending(int columnm,HDC hdc,HDC hdc_back) = 0;
	virtual int Search(int column,CString data,HDC hdc,HDC hdc_back) = 0;
	
	virtual int SetActive() = 0;
	virtual int SetInActive() = 0;

	virtual int IsTotalRow() = 0;
	virtual int IsTotalColumn() = 0;
	virtual int IsCurLine() = 0;
	virtual int IsFirstRow() = 0;
	virtual int IsFirstColumn() = 0;

	virtual int SetOnlySelect() = 0;
	virtual int GetData(int line,int column,CString &data) = 0;

	virtual int IsDataChange() = 0;

	virtual int SetBindData(int src,int trg) = 0;
	virtual int SetAutoNumSort(int column) = 0;
	virtual int SetAutoDuplicateDisableColumn(int column) = 0;

	virtual int MoveFirstLine(HDC hdc,HDC hdc_back) = 0;
	virtual int MoveLastLine(HDC hdc,HDC hdc_back)  = 0;

	virtual int SetTablePageButton() = 0;
	virtual int SetMultiSelection(int status) = 0;
	virtual int IsMultiCurLine(int index) = 0;
	virtual int SetMultiLimit(int limit) = 0;

	virtual int SetAutoHiddenSort(int column) = 0;
	////////////////////////////////////////
};

class CI_TABLE_GRID 
{
public:
	COLORREF mNull_BColor;
	COLORREF mNull_TColor;
	COLORREF mTitle_BRColor;
	COLORREF mTitle_TRColor;	
	COLORREF mTitle_BPColor;
	COLORREF mTitle_TPColor;	
	COLORREF mItem_PressColor;
	COLORREF mItem_ClickColor;
	COLORREF mItem_BRColor;
	COLORREF mItem_TRColor;
	COLORREF mItem_BPColor;
	COLORREF mItem_TPColor;
	int      mColumn_Limit;
	char     mTitle[100][200];
	char     mType[100][100];
	char     mFunction[100][100];
	char     mProperty[100][100];
	char     mRange[100][100];
	char     mDisplay[100][100];
	int      mWidth[100];

	
	CStringArray mDB[100];


	////////////////////////////////////////
	virtual int Init_Data() = 0;
	virtual int Init_Pos(POINT m_st,POINT m_et) = 0;
	virtual int Upload() = 0;
	
	virtual int Delete_Item(HDC hdc,HDC hdc_back) = 0;
	virtual int Insert_Item(HDC hdc,HDC hdc_back) = 0;
	virtual int Copy_Item(HDC hdc,HDC hdc_back) = 0;
	
	virtual int Draw(HDC hdc,HDC hdc_back) = 0;
	virtual int Draw_Button(int column,int line,CString title,HDC hdc,HDC hdc_back) = 0;
	virtual int CheckArea(POINT pt,HDC hdc,HDC hdc_back) = 0;
	
	virtual int SetFontName(CString fontname,int width,int height) = 0;
	
	virtual int Sort_Num_Ascending(int column,HDC hdc,HDC hdc_back) = 0;
	virtual int Sort_Ascending(int column,HDC hdc,HDC hdc_back) = 0;
	virtual int Sort_Descending(int columnm,HDC hdc,HDC hdc_back) = 0;
	virtual int Search(int column,CString data,HDC hdc,HDC hdc_back) = 0;
	
	virtual int SetActive() = 0;
	virtual int SetInActive() = 0;

	virtual int IsTotalRow() = 0;
	virtual int IsTotalColumn() = 0;
	virtual int IsCurLine() = 0;
	virtual int IsCurColumn() = 0;
	virtual int IsFirstRow() = 0;
	virtual int IsFirstColumn() = 0;

	virtual int SetColumnDisable(int column) = 0;
	virtual int IsColumnDisable(int column) = 0;

	virtual int IsDataChange() = 0;
	virtual int SetDataChange(int status) = 0;

	virtual	int SetAutoDuplicateDisableColumn(int column) = 0;
	virtual int CanSave(HDC hdc,HDC hdc_back) = 0;

	virtual int Clear(HDC hdc,HDC hdc_back) = 0;
	////////////////////////////////////////
};


class CI_TABLE_CSV 
{
public:
	//---------------------------------------------------------------------
	COLORREF mNull_BColor;
	COLORREF mNull_TColor;
	COLORREF mTitle_BRColor;
	COLORREF mTitle_TRColor;	
	COLORREF mTitle_BPColor;
	COLORREF mTitle_TPColor;	
	COLORREF mItem_PressColor;
	COLORREF mItem_ClickColor;
	COLORREF mItem_BRColor;
	COLORREF mItem_TRColor;
	COLORREF mItem_BPColor;
	COLORREF mItem_TPColor;
	int      mColumn_Limit;
	char     mTitle[100][200];
	char     mType[100][100];
	char     mFunction[100][100];
	char     mProperty[100][100];
	char     mRange[100][100];
	char     mDisplay[100][100];
	char     mDir[100][200];
	char     mExt[100][50];
	int      mWidth[100];

	
	CStringArray mDB[100];


	//---------------------------------------------------------------------
	virtual int Init_Data() = 0;
	virtual int Init_Pos(POINT m_st,POINT m_et) = 0;
	virtual int Upload() = 0;
	
	virtual int Delete_Item(HDC hdc,HDC hdc_back) = 0;
	virtual int Insert_Item(HDC hdc,HDC hdc_back) = 0;
	virtual int Copy_Item(HDC hdc,HDC hdc_back) = 0;
	
	virtual int Draw(HDC hdc,HDC hdc_back) = 0;
	virtual int Draw_Button(int column,int line,CString title,HDC hdc,HDC hdc_back) = 0;
	virtual int CheckArea(POINT pt,HDC hdc,HDC hdc_back) = 0;
	
	virtual int SetFontName(CString fontname,int width,int height) = 0;
	
	virtual int Sort_Num_Ascending(int column,HDC hdc,HDC hdc_back) = 0;
	virtual int Sort_Ascending(int column,HDC hdc,HDC hdc_back) = 0;
	virtual int Sort_Descending(int columnm,HDC hdc,HDC hdc_back) = 0;
	virtual int Search(int column,CString data,HDC hdc,HDC hdc_back) = 0;
	
	virtual int SetActive() = 0;
	virtual int SetInActive() = 0;

	virtual int IsTotalRow() = 0;
	virtual int IsTotalColumn() = 0;
	virtual int IsCurLine() = 0;
	virtual int IsCurColumn() = 0;
	virtual int IsFirstRow() = 0;
	virtual int IsFirstColumn() = 0;

	virtual int SetColumnDisable(int column) = 0;
	virtual int IsColumnDisable(int column) = 0;

	virtual int IsDataChange() = 0;
	virtual int SetDataChange(int status) = 0;

	virtual	int SetAutoDuplicateDisableColumn(int column) = 0;
	virtual int CanSave(HDC hdc,HDC hdc_back) = 0;

	virtual int Clear(HDC hdc,HDC hdc_back) = 0;

	virtual int Upload_Data() = 0;

	virtual int SetTablePageButton() = 0;
	virtual int SetMultiSelection(int status) = 0;
	virtual int IsMultiCurLine(int index) = 0;
	virtual int SetMultiLimit(int limit) = 0;
	virtual int Reset_AllSelected() = 0;

	virtual int Clear_Data() = 0;
	virtual int Clear_Data(int except_column) = 0;

	virtual int Set_AlarmMode(int status) = 0;
	virtual int Clear_AlarmList() = 0;
	virtual int Set_AlarmIndex(int index) = 0;

	virtual int Set_VScrollbar_RColor(COLORREF color) = 0;
	virtual int Set_VScrollbar_PColor(COLORREF color) = 0;
	//---------------------------------------------------------------------
};

class CI_TABLE_CSV_300
{
public:
	//---------------------------------------------------------------------
	COLORREF mNull_BColor;
	COLORREF mNull_TColor;
	COLORREF mTitle_BRColor;
	COLORREF mTitle_TRColor;	
	COLORREF mTitle_BPColor;
	COLORREF mTitle_TPColor;	
	COLORREF mItem_PressColor;
	COLORREF mItem_ClickColor;
	COLORREF mItem_BRColor;
	COLORREF mItem_TRColor;
	COLORREF mItem_BPColor;
	COLORREF mItem_TPColor;
	int      mColumn_Limit;
	char     mTitle[300][200];
	char     mType[300][100];
	char     mFunction[300][100];
	char     mProperty[300][100];
	char     mRange[300][100];
	char     mDisplay[300][100];
	char     mDir[300][200];
	char     mExt[300][50];
	int      mWidth[300];

	
	CStringArray mDB[300];


	//---------------------------------------------------------------------
	virtual int Init_Data() = 0;
	virtual int Init_Pos(POINT m_st,POINT m_et) = 0;
	virtual int Upload() = 0;
	
	virtual int Delete_Item(HDC hdc,HDC hdc_back) = 0;
	virtual int Insert_Item(HDC hdc,HDC hdc_back) = 0;
	virtual int Copy_Item(HDC hdc,HDC hdc_back) = 0;
	
	virtual int Draw(HDC hdc,HDC hdc_back) = 0;
	virtual int Draw_Button(int column,int line,CString title,HDC hdc,HDC hdc_back) = 0;
	virtual int CheckArea(POINT pt,HDC hdc,HDC hdc_back) = 0;
	
	virtual int SetFontName(CString fontname,int width,int height) = 0;
	
	virtual int Sort_Num_Ascending(int column,HDC hdc,HDC hdc_back) = 0;
	virtual int Sort_Ascending(int column,HDC hdc,HDC hdc_back) = 0;
	virtual int Sort_Descending(int columnm,HDC hdc,HDC hdc_back) = 0;
	virtual int Search(int column,CString data,HDC hdc,HDC hdc_back) = 0;
	
	virtual int SetActive() = 0;
	virtual int SetInActive() = 0;

	virtual int IsTotalRow() = 0;
	virtual int IsTotalColumn() = 0;
	virtual int IsCurLine() = 0;
	virtual int IsCurColumn() = 0;
	virtual int IsFirstRow() = 0;
	virtual int IsFirstColumn() = 0;

	virtual int SetColumnDisable(int column) = 0;
	virtual int IsColumnDisable(int column) = 0;

	virtual int IsDataChange() = 0;
	virtual int SetDataChange(int status) = 0;

	virtual	int SetAutoDuplicateDisableColumn(int column) = 0;
	virtual int CanSave(HDC hdc,HDC hdc_back) = 0;

	virtual int Clear(HDC hdc,HDC hdc_back) = 0;

	virtual int Upload_Data() = 0;

	virtual int SetTablePageButton() = 0;
	virtual int SetMultiSelection(int status) = 0;
	virtual int IsMultiCurLine(int index) = 0;
	virtual int SetMultiLimit(int limit) = 0;
	virtual int Reset_AllSelected() = 0;

	virtual int Clear_Data() = 0;
	virtual int Clear_Data(int except_column) = 0;

	virtual int Set_AlarmMode(int status) = 0;
	virtual int Clear_AlarmList() = 0;
	virtual int Set_AlarmIndex(int index) = 0;

	virtual int Set_VScrollbar_RColor(COLORREF color) = 0;
	virtual int Set_VScrollbar_PColor(COLORREF color) = 0;
	//---------------------------------------------------------------------
};


class CI_GRAPH
{
public:
	virtual void SetPosition(POINT st,POINT et) = 0;
	virtual void SetTitleName(CString title) = 0;
	virtual void SetTitleX(CString title) = 0;
	virtual void SetTitleY(CString title) = 0;
	virtual void SetRangeX(double min,double max) = 0;
	virtual void SetRangeY(double min,double max) = 0;
	virtual void ResetData() = 0;
	virtual void SetDataXY(double x,double y) = 0;
	virtual void Draw(HDC hdc,HDC hdc_back) = 0;
	virtual void Draw_Graph(HDC hdc,HDC hdc_back) = 0;
	virtual void Draw_Table(HDC hdc,HDC hdC_back) = 0;
	virtual void SetColor_Brush(COLORREF color) = 0;
	virtual void SetColor_Pen(COLORREF color) = 0;
	virtual void SetColor_TitleName(COLORREF color) = 0;
	virtual void SetColor_TitleX(COLORREF color) = 0;
	virtual void SetColor_TitleY(COLORREF color) = 0;
	virtual void SetColor_Index_Brush(COLORREF color) = 0;
	virtual void SetColor_Index_Pen(COLORREF color) = 0;
	virtual void SetColor_Index_X(COLORREF color) = 0;
	virtual void SetColor_Index_Y(COLORREF color) = 0;
	virtual void SetColor_Graph_Brush(COLORREF color) = 0;
	virtual void SetColor_Graph_Pen(COLORREF color) = 0;
	virtual void SetColor_Graph_Curve(COLORREF color) = 0;
	virtual void SetColor_Graph_Point(COLORREF color) = 0;
	virtual void SetColor_Graph_Dot(COLORREF color) = 0;
	virtual void SetGraphMarginX(int x) = 0;
	virtual void SetGraphMarginY(int y) = 0;
	virtual void SetResolutionX(int x) = 0;
	virtual void SetResolutionY(int y) = 0;
	virtual int  IsResolutionX() = 0;
	virtual int  IsResolutionY() = 0;
	virtual void Draw_LineX(double y,HDC hdc,HDC hdc_back) = 0;
	virtual void Draw_LineY(double x,HDC hdc,HDC hdc_back) = 0;
	virtual double IsClick(POINT pt,HDC hdc,HDC hdc_back) = 0;
	virtual int  ClearMinMax() = 0;
	virtual int  SetMinMax(double time) = 0;
	virtual double GetMinTime() = 0;
	virtual double GetMaxTime() = 0;
	virtual double GetMaxX() = 0;
	virtual double GetMinX() = 0;
	virtual double GetMaxY() = 0;
	virtual double GetMinY() = 0;
	virtual int  SetMinMode() = 0;
	virtual int  SetMaxMode() = 0;
	virtual void SetDataXY(int index,double x,double y) = 0;

	virtual int SetDisplayInteger() = 0;
	virtual int SetDisableMinMax()  = 0;
};

class CI_PROGRAM_CONTROL
{
public:
	virtual int  SetPosition(POINT pt) = 0;
	virtual HWND Control(char *dir,char *path,int sec,char *title,int show) = 0;
	virtual int  Start_Program(CString dir,CString program) = 0;
	virtual int  Start_Program_Ex(CString dir,CString program,CString cmmd1,CString cmmd2) = 0;
};
