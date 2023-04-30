#pragma once


extern HTREEITEM MACRO__Get_HTREEITEM_Of_N_Node(CTreeCtrl* p_tree, 
												const int node_index);

extern void MACRO__Expand_All_Tree(CTreeCtrl* p_tree);
extern void MACRO__Expand_Tree(CTreeCtrl* p_tree, 
							   HTREEITEM h_node, 
							   const int child_size);

extern void MACRO__Contract_All_Tree(CTreeCtrl* p_tree);
extern void MACRO__Contract_Tree(CTreeCtrl* p_tree, 
								 HTREEITEM h_node);

extern int MACRO__Get_Dir_Time_List(const CString& dir_root,
									CStringArray&  l_dir_name,
									CStringArray&  l_dir_time);
extern int MACRO__Get_Dir_Date_List(const CString& dir_root,
							        CStringArray&  l_dir_name,
							        CStringArray&  l_dir_date);
extern int MACRO__Get_File_List(const CString& dir_root,
							    const CString& file_ext,
							    CStringArray&  l_file_name,
							    CStringArray&  l_file_date);

extern void MACRO__Convert__LIST(const char parc, 
							     const CString& string,
							     CStringArray& data_list,
								 const int array_max = -1);

extern int MACRO__Get_Data_List_Of_File(const CString& file_path, 
								        CStringArray& l_line,
										const CString& keyword_01,
										const CString& keyword_02);
extern int MACRO__Get_File_Data(const CString& file_path, 
							    CStringArray& l_line);
extern int MACRO__Get_File_Data(const CString& file_path, 
								CString& file_data);
extern int MACRO__Get_Line_List_From_File_Data(const CString& file_data, 
											   CStringArray& l_line);

extern CString MACRO__Get_Current_Date();
extern CString MACRO__Get_Current_Time();

extern void MACRO__Change_Order(CStringArray& l_date,
								const bool order_type__descending,
								const bool active__number_check = false);

extern CString MACRO__Get_String_With_No_Space(const CString& str_org);
extern CString MACRO__Get_String_With_No_Char(const CString& str_org, 
											  const char ch_check);

extern CString MACRO__Convert_No_Number_To_Removal(const CString& str_data);

extern int MACRO__Make_File_Data(const CString& file_path, 
								 const CString& file_data,
								 const bool open_mode);

extern CString MACRO__Trim_Left_String(const CString& str_org);
extern CString MACRO__Trim_Right_String(const CString& str_org);

extern int MACRO__Search_Index_Of_StringArray(const CStringArray& l_str, 
											  const CString& str_name);

extern int MACRO__Get_PMx_ID(const CString& str_md);
extern int MACRO__Get_LLx_ID(const CString& str_md);

extern CString MACRO__Get_Dir_Path(const CString& file_path);
extern CString MACRO__Get_File_Name(const CString& file_path);

extern void MACRO__Cal_Tack_Time(const CStringArray& l_start_time,
								 const CStringArray& l_end_time,
								 CStringArray& l_tack_time);


extern CString MACRO__Get_ITEM_DATA(const CString item_data, const char ch_sep);

extern int MACRO__Check_Stringarray(const CString istr_data, const CStringArray& l_data);
extern int MACRO__Get_Count_Of_Stringarray(const CString str_data, const CStringArray& l_data);
