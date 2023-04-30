#pragma once


extern int  MACRO__Get__PMC_ID(const CString& pmx_name);
extern int  MACRO__Get__LLx_ID(const CString& llx_name);

extern void MACRO__Convert__MIN_MAX(const CString& min_max_str,
									CString& min_data,
									CString& max_data);

extern void MACRO__Convert__LIST(const char parc,const CString& string,
								 CStringArray& data_list);

extern int  MACRO__Get_Dir_Date_List(const CString& dir_root,
									 CStringArray&  l_dir_name,
									 CStringArray&  l_dir_date);

extern int  MACRO__Get_File_List(const CString& dir_root,
								 const CString& file_ext,
								 CStringArray&  l_file_name,
								 CStringArray&  l_file_date);

extern CString MACRO__Get_Date_Time();

extern int  MACRO__Get_File_Data(const CString& file_path, CString& file_data);
extern int  MACRO__Get_Line_List_From_File_Data(const CString& file_data, CStringArray& l_line);
extern int  MACRO__Save_File_Data(const CString& file_path, const CString& file_data);
extern int  MACRO__Delete_File(const CString& file_path);

extern void MACRO__Expand_All_Tree(CTreeCtrl* p_tree);
extern void MACRO__Expand_Tree(CTreeCtrl* p_tree, HTREEITEM h_node, const int child_size);

extern void MACRO__Contract_All_Tree(CTreeCtrl* p_tree);
extern void MACRO__Contract_Tree(CTreeCtrl* p_tree, HTREEITEM h_node);

extern CString MACRO__Get_ITEM_DATA(const CString str_data, const char ch_sep);

extern int MACRO__Check_Route_File_Edit_Type(const CString& file_data);
