#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "CLS__Proc_Log.h"
#include "Macro_Function.h"


// ...
CLS__Proc_Log::CLS__Proc_Log()
{
	bActive__CH_MIN = true;
	bActive__CH_MAX = true;
	bActive__CH_AVG = true;

	bActive__Event_Channel    = true;
	bActive__Interval_Channel = true;
}
CLS__Proc_Log::~CLS__Proc_Log()
{

}

// ...
void CLS__Proc_Log::Set__Dir_Root(const CString& dir_root)
{
	sDir__Temp_Log  = dir_root;
	sDir__Temp_Log += "\\_TEMP_LOG";

	sPath__Log_Viewer_Inf.Format("%s\\%s", sDir__Temp_Log,"LogViewer.inf");
	sPath__Log_Viewer_Txt.Format("%s\\%s", sDir__Temp_Log,"LogViewer.txt");
}
void CLS__Proc_Log::Set_Template___Only_Analog()
{
	bActive__Event_Channel    = false;
	bActive__Interval_Channel = true;
}

// ...
#define CFG__ITEM_MAX			300

int  CLS__Proc_Log::Update__Template_File(const HWND hwnd, const CString& file_path)
{
	CString file_data;

	if(_Read__File_Path(hwnd, file_path,file_data) < 0)
	{
		return -1;
	}

	// ...
	CStringArray l_channel;
	CStringArray l_title;
	CStringArray l_log_type;
	CStringArray l_ch_type;

	// ...
	{
		CString word;

		int db_index = 0;
		int para = 0;

		int limit = file_data.GetLength();
		int i;

		for(i=0; i<limit; i++)
		{
			char ch = file_data.GetAt(i);

			if((ch == ',')
			|| (ch == '\n'))
			{
				para++;

				if(word.GetLength() > 0)
				{
					if(para == 1)
					{
						db_index = l_channel.GetSize();

						l_channel.Add(word);
						l_title.Add("");
						l_log_type.Add("");
						l_ch_type.Add("");
					}
					else if(para == 2)				l_title[db_index]    = word;
					else if(para == 3)				l_log_type[db_index] = word;
					else if(para == 4)				l_ch_type[db_index]  = word;

					word = "";
				}
			}
			else
			{
				word += ch;
			}

			if(ch == '\n')
			{
				para = 0;
			}
		}
	}

	// ...
	{
		mTable_Event_Item.RemoveAll();
		mTable_Event_Title.RemoveAll();

		mTable_Interval_Item.RemoveAll();
		mTable_Interval_Title.RemoveAll();
	}

	// ...
	{
		int limit = l_channel.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			CString log_type = l_log_type[i];

			CString ch_name   = l_channel[i];
			CString str_title = l_title[i];
			CString ch_tyoe   = l_ch_type[i];

			if(log_type.CompareNoCase("EVENT") == 0)
			{
				if(!bActive__Event_Channel)				continue;

				mTable_Event_Item.Add(ch_name);
				mTable_Event_Title.Add(str_title);
			}
			else 
			{
				if(!bActive__Interval_Channel)			continue;
				if(ch_tyoe.CompareNoCase("A") != 0)		continue;

				mTable_Interval_Item.Add(ch_name);
				mTable_Interval_Title.Add(str_title);
			}
		}
	}

	return 1;
}
int  CLS__Proc_Log::_Read__File_Path(const HWND hwnd,
									 const CString& file_path,
									 CString& file_data)
{
	FILE *fp = fopen(file_path, "r");

	if(fp == NULL)
	{
		MessageBox(hwnd, file_path, "Read_File_from_SEQ() : File Path - Error !",MB_OK|MB_TOPMOST);
		return -1;
	}

	fseek(fp,0,SEEK_END);
	int totalbytes = ftell(fp);

	char *p_file = new char[totalbytes+1];
	if(p_file == NULL)
	{
		MessageBox(hwnd, file_path,"Read_File_from_SEQ() : File Memory Allocation - Error !",MB_OK|MB_TOPMOST);
		return - 1;
	}

	rewind(fp);

	// ...
	int numread = fread(p_file,1,totalbytes,fp);
	p_file[numread] = 0;

	fclose(fp);

	file_data.Format("%s", p_file);
	delete [] p_file;

	return 1;
}

int  CLS__Proc_Log::
Get__Template_Event(CStringArray& l_name, CStringArray& l_channel)
{
	l_name.Copy(mTable_Event_Title);
	l_channel.Copy(mTable_Event_Item);
	return 1;
}

int  CLS__Proc_Log::
Get__Template_Interrval(CStringArray& l_name, 
						CStringArray& l_channel)
{
	CStringArray l_log_cnt;

	return Get__Template_Interrval(l_name, l_channel, l_log_cnt);
}
int  CLS__Proc_Log::
Get__Template_Interrval(CStringArray& l_name, 
						CStringArray& l_channel,
						CStringArray& l_log_cnt)
{
	l_name.Copy(mTable_Interval_Title);
	l_channel.Copy(mTable_Interval_Item);
	l_log_cnt.RemoveAll();

	//
	CString str_data;

	int i_limit = l_channel.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		int log_cnt = mProc__XY_Data.Get__All_Y_Data(l_channel[i]);
		if(log_cnt < 0)			log_cnt = 0;

		str_data.Format("%1d", log_cnt);
		l_log_cnt.Add(str_data);
	}
	return 1;
}


// ...
int  CLS__Proc_Log::
Make__Log_Txt_File(const HWND hwnd,
				   const CString& log_path,
				   const CString& log_file,
				   const CString& template_name)
{
	CString file_data;

	if(_Read__File_Path(hwnd, log_path,file_data) < 0)
	{
		return -1;
	}

	// ...
	CString string;
	string.Format("%s\n%s\n%s\n%s\n",
				  "[VIEW]",  
				  "LogViewer.txt",
				  log_file,
				  template_name);

	CStringArray l__file_data;
	l__file_data.Add(string);	

	// ...
	CString line_word;
	CString str_word;
	CString name_str;
	CString data_str;
	CString time_str;
	CString title_str;
	char ch;
	int fnc_num;
	int under_line;
	int para;
	int interval_flag;

	str_word = "";
	interval_flag = -1;
	fnc_num = -1;
	para = 0;
	under_line = 0;

	CString channel, event_channel, event_data;

	int channel_count = 0;

	CString l__ch_data[CFG__ITEM_MAX];
	CString l__ch_min[CFG__ITEM_MAX];
	CString l__ch_max[CFG__ITEM_MAX];
	CString l__ch_avg[CFG__ITEM_MAX];

	CString getLine="";
	CString str_line = "";

	// ...
	int limit_ch = file_data.GetLength();
	int i_ch;

	for(i_ch=0; i_ch<limit_ch; i_ch++)
	{
		ch = file_data.GetAt(i_ch);

		if((ch == '\n')
		|| (ch ==  ',')
		|| (ch == ';')
		|| (ch ==  ' ')
		|| (ch == '$'))
		{
			if(str_word.GetLength() > 0)
			{
				if(str_word.Compare("#1") == 0)
				{
					fnc_num = 1;
				}
				else if(str_word.Compare("#2") == 0)
				{
					fnc_num = 2;
				}
				else if(str_word.Find("#STEP_MIN")>=0)
				{
					fnc_num = 4;
				}
				else if(str_word.Find("#STEP_MAX")>=0)
				{
					fnc_num = 5;
				}
				else if(str_word.Find("#STEP_AVG")>=0)
				{
					fnc_num = 6;
				}
				else
				{
					if(fnc_num == 1)
					{
						str_line += str_word;
						str_line += " ";
					}
					else if(fnc_num == 2)
					{

						time_str = str_word;
					}
					else if(fnc_num == 3)
					{
						para++;

						if(para == 1)
						{
							channel = str_word;

							if(channel_count == 0)		
								event_channel = str_word;	
						}
						else if(para == 2)
						{
							int k_limit = mTable_Interval_Item.GetSize();
							if(k_limit > CFG__ITEM_MAX)			k_limit = CFG__ITEM_MAX;

							for(int k=0;k<k_limit;k++)
							{
								if(channel.CompareNoCase(mTable_Interval_Item[k]) != 0)
									continue;

								// ...
								l__ch_data[k] = str_word;

								channel_count++;
								break;
							}

							if(channel_count == 0)		
								event_data = str_word;
						}
					}
					else if(fnc_num == 4 || fnc_num == 5 || fnc_num == 6)
					{
						para++;

						if(para == 1)
						{
							channel = str_word;
						}
						else if(para == 2)
						{
							int k_limit = mTable_Interval_Item.GetSize();
							if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

							for(int k=0; k<k_limit; k++)
							{
								if(channel.CompareNoCase(mTable_Interval_Item[k]) != 0)
									continue;

								// ...
								{
										 if(fnc_num == 4)		l__ch_min[k] = str_word;
									else if(fnc_num == 5)		l__ch_max[k] = str_word;
									else if(fnc_num == 6)		l__ch_avg[k] = str_word;
								}

								channel_count++;
								break;
							}							
						}
					}
					else		// fnc_num == -1 $뒤 #없는 문자는 그냥 그대로 찍어 버려..
					{
						getLine += str_word;
					}
				}
			}

			str_word = "";
		}
		else 
		{
			str_word += ch;
		}

		if(ch == '\n') 
		{
			if(fnc_num == -1)
			{
				if(getLine.GetLength() > 0)
				{
					CString tmp_line = getLine;

					l__file_data.Add(tmp_line);
					int file_index = l__file_data.GetSize() - 1;

					int k_limit = mTable_Interval_Item.GetSize();
					for(int k=1; k<k_limit; k++)
					{
						tmp_line.Format("--------------------");
						l__file_data[file_index] += tmp_line;
					}

					getLine = "";
				}
			}

			if(fnc_num == 1)
			{
				CString msg;
				CString bff;

				msg.Format(" Datalog Report of File : ..\\%s", log_file);
				l__file_data.Add(msg);

				msg.Format("  %s\n",str_line);
				l__file_data.Add(msg);

				msg = " hh:mm:ss  ";

				int k_limit = mTable_Interval_Item.GetSize();
				for(int k=0; k<k_limit; k++)
				{
					bff.Format("%20s", mTable_Interval_Title[k]); 
					msg += bff;
				}
				msg += "\n"; 

				l__file_data.Add(msg);

				under_line = msg.GetLength();
				msg = "";

				for(int i=0; i<under_line; i++)
				{
					msg += "-"; 
				}
				msg += "\n";

				l__file_data.Add(msg);

				str_line = "";
				fnc_num = -1;
			}
			if(fnc_num == 2)	fnc_num = 3;

			para = 0;
			channel = "";
		}

		if(ch == '$')
		{
			if(fnc_num == 3)
			{
				if(channel_count == 0)
				{
					int k_limit = mTable_Event_Item.GetSize();

					for(int k=0; k<k_limit; k++)
					{
						if(event_channel.CompareNoCase(mTable_Event_Item[k]) != 0)
							continue;

						// ...
						CString str;

						str.Format("%s : %s -> %s",
									time_str,
									mTable_Event_Title[k],
									event_data);

						l__file_data.Add(str);
						break;
					}
				}
				else 
				{
					CString str_bff;

					l__file_data.Add(time_str);
					int file_index = l__file_data.GetSize() - 1;

					int k_limit = mTable_Interval_Item.GetSize();
					if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

					for(int k=0; k<k_limit; k++)
					{
						str_bff.Format("%19s ", l__ch_data[k]);
						l__file_data[file_index] += str_bff;
					}
				}
			} 
			else if(fnc_num == 4 || fnc_num == 5 ||fnc_num == 6)
			{
				if(channel_count == 0)
				{

				}
				else 
				{
					CString ttmp;

					int k_limit = mTable_Interval_Item.GetSize();					
					if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

					if(fnc_num == 4)		
					{
						if(bActive__CH_MIN)
						{
							l__file_data.Add("         MIN : ");
							int file_index = l__file_data.GetSize() - 1;

							for(int k=0; k<k_limit; k++)
							{
								ttmp.Format("%19s ", l__ch_min[k]);
								l__file_data[file_index] += ttmp;
							}
						}
					} 
					else if(fnc_num == 5)		
					{
						if(bActive__CH_MAX)
						{	
							l__file_data.Add("         MAX : ");
							int file_index = l__file_data.GetSize() - 1;

							for(int k=0; k<k_limit; k++)
							{
								ttmp.Format("%19s ", l__ch_max[k]);
								l__file_data[file_index] += ttmp;
							}
						}
					}
					else if(fnc_num == 6)		
					{
						if(bActive__CH_AVG)
						{
							l__file_data.Add("         AVG : ");
							int file_index = l__file_data.GetSize() - 1;

							for(int k=0; k<k_limit; k++)
							{
								ttmp.Format("%19s ", l__ch_avg[k]);
								l__file_data[file_index] += ttmp;
							}
						}
					}

					ttmp = "";
				}
			}

			channel_count = 0;
			str_line = "";
			time_str = "";
			fnc_num = -1;

			event_channel = "";
			event_data = "";

			// ...
			{
				int k_limit = mTable_Interval_Item.GetSize();
				if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

				for(int k=0;k<k_limit;k++)
				{
					l__ch_data[k] = "";

					l__ch_min[k] = "";
					l__ch_max[k] = "";
					l__ch_avg[k] = "";
				}
			}
		}
	}

	// ...
	{
		CreateDirectory(sDir__Temp_Log, NULL);

		FILE *out = fopen(sPath__Log_Viewer_Inf, "w");
		if(out != NULL)
		{
			if(l__file_data.GetSize() > 0)
				fputs(l__file_data[0],out);
			
			fclose(out);
		}

		out = fopen(sPath__Log_Viewer_Txt, "w");
		if(out != NULL)
		{
			int limit = l__file_data.GetSize();

			for(int i=1; i<limit; i++)
			{
				fputs(l__file_data[i], out);
				fputs("\n",out);
			}

			fclose(out);
		}
	}

	return 1;
}
int  CLS__Proc_Log::
Make__Log_Csv_File(const HWND hwnd,
				   const CString& log_path,
				   const CString& log_file,
				   const CString& template_name,
				   const CString& out_path,
				   const bool align_left)
{
	CString file_data;

	if(_Read__File_Path(hwnd, log_path,file_data) < 0)
	{
		return -1;
	}

	// ...
	CStringArray l__file_data;

	// ...
	CString channel, event_channel, event_data;

	int channel_count = 0;

	CString l__ch_data[CFG__ITEM_MAX];
	CString l__ch_min[CFG__ITEM_MAX];
	CString l__ch_max[CFG__ITEM_MAX];
	CString l__ch_avg[CFG__ITEM_MAX];
	CString getLine = "";

	CString str_line = "";

	// ...
	CString line_word;
	CString str_word;
	CString name_str;
	CString data_str;
	CString time_str;
	CString title_str;

	int fnc_num;
	int under_line;
	int para;
	int interval_flag;

	str_word = "";
	interval_flag = -1;
	fnc_num = -1;
	para = 0;
	under_line = 0;

	// ...
	int limit_ch = file_data.GetLength();
	int i_ch;

	for(i_ch=0; i_ch<limit_ch; i_ch++)
	{
		char ch = file_data.GetAt(i_ch);

		if((ch == '\n')
		|| (ch ==  ',')
		|| (ch == ';')
		|| (ch ==  ' ')
		|| (ch == '$'))
		{
			if(str_word.GetLength() > 0)
			{
				if(str_word.Compare("#1") == 0)
				{
					fnc_num = 1;
				}
				else if(str_word.Compare("#2") == 0)
				{
					fnc_num = 2;
				}
				else if(str_word.Find("#STEP_MIN")>=0)
				{
					fnc_num = 4;
				}
				else if(str_word.Find("#STEP_MAX")>=0)
				{
					fnc_num = 5;
				}
				else if(str_word.Find("#STEP_AVG")>=0)
				{
					fnc_num = 6;
				}
				else
				{
					if(fnc_num == 1)
					{
						str_line += str_word;
						str_line += " ";
					}
					else if(fnc_num == 2)
					{

						time_str = str_word;
					}
					else if(fnc_num == 3)
					{
						para++;

						if(para == 1)
						{
							channel = str_word;

							if(channel_count == 0)
								event_channel = str_word;
						}
						else if(para == 2)
						{
							int k_limit = mTable_Interval_Item.GetSize();
							if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

							for(int k=0; k<k_limit; k++)
							{
								if(channel.CompareNoCase(mTable_Interval_Item[k]) != 0)
									continue;

								// ...
								l__ch_data[k] = str_word;

								channel_count++;
								break;
							}
	
							if(channel_count == 0)
								event_data = str_word;
						}
					}
					else if(fnc_num == 4 || fnc_num == 5 || fnc_num == 6)
					{
						para++;

						if(para == 1)
						{
							channel = str_word;
						}
						else if(para == 2)
						{
							int k_limit = mTable_Interval_Item.GetSize();
							if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

							for(int k=0; k<k_limit; k++)
							{
								if(channel.CompareNoCase(mTable_Interval_Item[k]) != 0)
									continue;

								// ...
								{
										 if(fnc_num == 4)		l__ch_min[k] = str_word;
									else if(fnc_num == 5)		l__ch_max[k] = str_word;
									else if(fnc_num == 6)		l__ch_avg[k] = str_word;
								}

								channel_count++;
								break;
							}							
						}
					}
					else 
					{
						getLine += str_word;
					}
				}
			}

			str_word = "";
		}
		else 
		{
			str_word += ch;
		}

		if(ch == '\n') 
		{
			if(fnc_num == -1)
			{
				if(getLine.GetLength()>0)
				{
					CString tmp_line = getLine;
					
					l__file_data.Add(tmp_line);
					int file_index = l__file_data.GetSize() - 1;

					int k_limit = mTable_Interval_Item.GetSize();
					for(int k=1; k<k_limit; k++)
					{
						tmp_line.Format("---------------,");
						l__file_data[file_index] += tmp_line;
					}

					getLine = "";
				}
			}
			if(fnc_num == 1)
			{
				CString msg;

				msg.Format(" Datalog Report of File : ..\\%s", log_file);
				l__file_data.Add(msg);

				msg.Format("  %s\n",str_line);
				l__file_data.Add(msg);

				// ...
				CString bff;

				msg = " hh:mm:ss  ";

				int k_limit = mTable_Interval_Item.GetSize();

				for(int k=0; k<k_limit; k++)
				{
					if(align_left)			bff.Format("%-20s", mTable_Interval_Title[k]); 
					else					bff.Format("%20s", mTable_Interval_Title[k]); 

					msg += ",";
					msg += bff;
				}
				msg += "\n"; 

				l__file_data.Add(msg);

				str_line = "";
				fnc_num = -1;
			}
			if(fnc_num == 2)	fnc_num = 3;

			para = 0;
			channel = "";
		}
		if(ch == '$')
		{
			if(fnc_num == 3)
			{
				if(channel_count == 0)
				{
					int k_limit = mTable_Event_Item.GetSize();

					for(int k=0; k<k_limit; k++)
					{
						if(event_channel.CompareNoCase(mTable_Event_Item[k]) != 0)
							continue;

						// ...
						CString str;

						str.Format("%s, %s -> %s,",
									time_str,
									mTable_Event_Title[k],
									event_data);

						l__file_data.Add(str);
						break;
					}
				}
				else 
				{
					CString str_bff;

					l__file_data.Add(time_str);
					int file_index = l__file_data.GetSize() - 1;
					l__file_data[file_index] += ",";

					int k_limit = mTable_Interval_Item.GetSize();
					if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

					for(int k=0; k<k_limit; k++)
					{
						if(align_left)			str_bff.Format("%-20s,", l__ch_data[k]);
						else					str_bff.Format("%20s,",  l__ch_data[k]);

						l__file_data[file_index] += str_bff;
					}
				}
			} 
			else if(fnc_num == 4 || fnc_num == 5 ||fnc_num == 6)
			{
				if(channel_count == 0)
				{

				}
				else 
				{
					CString ttmp;

					int k_limit = mTable_Interval_Item.GetSize();
					if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

					if(fnc_num == 4)		
					{
						if(bActive__CH_MIN)
						{
							l__file_data.Add("\tMIN : ,");
							int file_index = l__file_data.GetSize() - 1;

							for(int k=0; k<k_limit; k++)
							{
								if(align_left)			ttmp.Format("%-20s,", l__ch_min[k]);
								else					ttmp.Format("%20s,",  l__ch_min[k]);

								l__file_data[file_index] += ttmp;
							}
						}
					} 
					else if(fnc_num == 5)		
					{
						if(bActive__CH_MAX)
						{	
							l__file_data.Add("\tMAX : ,");
							int file_index = l__file_data.GetSize() - 1;

							for(int k=0; k<k_limit; k++)
							{
								if(align_left)			ttmp.Format("%-20s,", l__ch_max[k]);
								else					ttmp.Format("%20s,",  l__ch_max[k]);

								l__file_data[file_index] += ttmp;
							}
						}
					}
					else if(fnc_num == 6)		
					{
						if(bActive__CH_AVG)
						{	
							l__file_data.Add("\tAVG : ,");
							int file_index = l__file_data.GetSize() - 1;

							for(int k=0; k<k_limit; k++)
							{
								if(align_left)			ttmp.Format("%-20s,", l__ch_avg[k]);
								else					ttmp.Format("%20s,",  l__ch_avg[k]);

								l__file_data[file_index] += ttmp;
							}
						}
					}

					ttmp = "";
				}
			}

			channel_count = 0;
			str_line = "";
			time_str = "";
			fnc_num = -1;

			event_channel = "";
			event_data = "";

			// ...
			{
				int k_limit = mTable_Interval_Item.GetSize();
				if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

				for(int k=0; k<k_limit; k++)
				{
					l__ch_data[k] = "";

					l__ch_min[k] = "";
					l__ch_max[k] = "";
					l__ch_avg[k] = "";
				}
			}
		}
	}

	// ....
	{
		FILE *out = fopen(out_path, "w");

		if(out != NULL)
		{
			int limit = l__file_data.GetSize();

			for(int i=1;i<limit;i++)
			{
				fputs(l__file_data[i], out);
				fputs("\n",out);
			}

			fclose(out);
		}
	}

	return 1;
}

int  CLS__Proc_Log::
Upload__Proc_Data_Of_Log_File(const HWND hwnd, 
						      const CString& log_path)
{
	mProc__XY_Data.Clear();

	// ...
	CString file_data;

	if(_Read__File_Path(hwnd, log_path,file_data) < 0)
	{
		return -1;
	}

	// ...
	CString str_word;
	CString time_str;
	double x_sec = 0;

	int fnc_num = -1;
	int para = 0;
	int interval_flag = -1;

	CString channel;
	int channel_count = 0;

	CStringArray l__ch_name;
	CStringArray l__ch_data;

	// ...
	int limit_ch = file_data.GetLength();
	int i_ch;

	for(i_ch=0; i_ch<limit_ch; i_ch++)
	{
		char ch = file_data.GetAt(i_ch);

		if((ch == '\n')
		|| (ch ==  ',')
		|| (ch == ';')
		|| (ch ==  ' ')
		|| (ch == '$'))
		{
			if(str_word.GetLength() > 0)
			{
				if(str_word.Compare("#1") == 0)
				{
					fnc_num = 1;
				}
				else if(str_word.Compare("#2") == 0)
				{
					fnc_num = 2;
					channel_count = 0;

					l__ch_name.RemoveAll();
					l__ch_data.RemoveAll();
				}
				else if(str_word.Find("#STEP_MIN") >=0)
				{
					fnc_num = 4;
				}
				else if(str_word.Find("#STEP_MAX") >=0)
				{
					fnc_num = 5;
				}
				else if(str_word.Find("#STEP_AVG") >=0)
				{
					fnc_num = 6;
				}
				else
				{
					if(fnc_num == 1)
					{

					}
					else if(fnc_num == 2)
					{
						time_str = str_word;

						// ...
						x_sec = 0;

						CStringArray l_para;
						MACRO__Convert__LIST(':', time_str, l_para);

						int i_limit = l_para.GetSize();
						int i;

						for(i=0; i<i_limit; i++)
						{
							if(i > 0)		x_sec *= 60;
							x_sec += atof(l_para[i]);
						}
					}
					else if(fnc_num == 3)
					{
						para++;

						if(para == 1)
						{
							channel = str_word;
						}
						else if(para == 2)
						{
							int k_limit = mTable_Interval_Item.GetSize();
							if(k_limit > CFG__ITEM_MAX)			k_limit = CFG__ITEM_MAX;

							for(int k=0;k<k_limit;k++)
							{
								if(channel.CompareNoCase(mTable_Interval_Item[k]) != 0)
									continue;

								l__ch_name.Add(channel);
								l__ch_data.Add(str_word);

								channel_count++;
								break;
							}
						}
					}
					else if(fnc_num == 4 || fnc_num == 5 || fnc_num == 6)
					{

					}
				}
			}

			str_word = "";
		}
		else 
		{
			str_word += ch;
		}

		if(ch == '\n') 
		{
			if(fnc_num == 1)		fnc_num = -1;
			if(fnc_num == 2)		fnc_num = 3;

			para = 0;
			channel = "";
		}

		if(ch == '$')
		{
			if(fnc_num == 3)
			{
				if(channel_count == 0)
				{

				}
				else 
				{
					mProc__XY_Data.Load__XY_Data(x_sec, l__ch_name,l__ch_data);
				}
			} 
			else if(fnc_num == 4 || fnc_num == 5 ||fnc_num == 6)
			{

			}

			channel_count = 0;
			fnc_num = -1;

			time_str = "";
			x_sec = 0;

			l__ch_name.RemoveAll();
			l__ch_data.RemoveAll();
		}
	}

	return 1;
}
CProc_Log__XY_Data* CLS__Proc_Log::Get_Addr__Proc_XY_Data()
{
	return &mProc__XY_Data;
}

int  CLS__Proc_Log::
Upload__Proc_Step_Of_Log_File(const HWND hwnd, 
							  const CString& log_path)
{
	mProc_Step.Clear();

	printf("Upload__Proc_Step_Of_Log_File() ... \n");
	printf(" * log_path <- [%s] \n", log_path);

	// ...
	CStringArray l_line;

	if(MACRO__Get_File_Data(log_path, l_line) < 0)
	{
		printf(" ** error !!! \n");
		return -1;
	}

	// ...
	CStringArray l__step_id;
	CStringArray l__step_start;
	CStringArray l__step_end;

	bool active_start = false;
	bool active_end   = false;

	CString key_name;
	int s_index;

	// ...
	int i_limit = l_line.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_line = l_line[i];
		
		key_name = "#STEP_START=";
		s_index = str_line.Find(key_name);
		if(s_index >= 0)
		{
			active_start = true;
			active_end   = false;
		}
		else
		{
			key_name = "#STEP_END=";
			s_index = str_line.Find(key_name);
			if(s_index < 0)			continue;

			active_start = false;
			active_end   = true;
		}

		str_line.Delete(s_index, s_index+key_name.GetLength());				

		if((active_start) || (active_end))
		{
			CStringArray l_para;
			MACRO__Convert__LIST(',', str_line,l_para);

			CString str_id;
			CString str_time;

			if(l_para.GetSize() > 0)		str_id   = l_para[0];
			if(l_para.GetSize() > 1)		str_time = l_para[1];

			if(active_start)
			{
				l__step_id.Add(str_id);
				l__step_start.Add(str_time);
				l__step_end.Add("");
			}
			else if(active_end)
			{
				int db_i = l__step_end.GetSize() - 1;
				if(db_i >= 0)		l__step_end[db_i] = str_time;
			}
		}
	}

	// ...
	{
		CStringArray l__tack_time;
		MACRO__Cal_Tack_Time(l__step_start,l__step_end, l__tack_time);

		mProc_Step.sList__Step_ID.Copy(l__step_id);
		mProc_Step.sList__Step_Start.Copy(l__step_start);
		mProc_Step.sList__Step_End.Copy(l__step_end);
		mProc_Step.sList__Step_Tack.Copy(l__tack_time);
	}
	return 1;
}
