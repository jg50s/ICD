#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Lot_Process.h"
#include "Macro_Function.h"

#include <math.h>
#include <vector>
#include <sstream>

using namespace std;


// ...
void CDlg__Lot_Process::_Init__Proc_Chart()
{
	RECT rc;
	mChart_Viwer.GetClientRect(&rc);

	rc.top -= 1;
	rc.right -= 1;

	mArea__Chart_View = rc;

	// ...
	{
		int i_limit = _CFG__SLOT_MAX;

		for(int i=0; i<i_limit; i++)
		{
			int g_color = 0;
			int r_color = 0;
			int b_color = 0;

				 if(i == 0)			r_color = 255;
			else if(i == 1)			r_color = 175;
			else if(i == 2)			r_color = 95;
			else if(i == 3)			g_color = 255;
			else if(i == 4)			g_color = 175;
			else if(i == 5)			g_color = 95;
			else if(i == 6)			b_color = 255;
			else if(i == 7)			b_color = 175;
			else if(i == 8)			b_color = 95;
			else if(i == 9)			;
			else if(i == 10)
			{
				r_color = 255;
				g_color = 255;
			}
			else if(i == 11)
			{
				r_color = 175;
				g_color = 175;
			}
			else if(i == 12)
			{
				r_color = 95;
				g_color = 95;
			}
			else if(i == 13)
			{
				g_color = 255;
				b_color = 255;
			}
			else if(i == 14)
			{
				g_color = 175;
				b_color = 175;
			}
			else if(i == 15)
			{
				g_color = 95;
				b_color = 95;
			}
			else if(i == 16)
			{
				b_color = 255;
				r_color = 255;
			}
			else if(i == 17)
			{
				b_color = 175;
				r_color = 175;
			}
			else if(i == 18)
			{
				b_color = 95;
				r_color = 95;
			}
			else if(i == 20)
			{
				g_color = 175;
				r_color = 175;
				b_color = 175;
			}
			else if(i == 21)
			{
				g_color = 255;
				r_color = 95;
				b_color = 95;
			}
			else if(i == 22)
			{
				g_color = 95;
				r_color = 255;
				b_color = 95;
			}
			else if(i == 23)
			{
				g_color = 95;
				r_color = 95;
				b_color = 255;
			}
			else if(i == 24)
			{
				g_color = 95;
				r_color = 95;
				b_color = 95;
			}

			int rgb_color = b_color + (g_color * 0x100) + (r_color * 0x10000);
			cPara__Slot_Color_ARGB[i] = rgb_color;

			cPara__Slot_Color_RGB[i] = RGB(r_color,g_color,b_color);
		}

		// ...
		{
			int r_color = 0;
			int g_color = 128;
			int b_color = 255;

			cPara__Single_Color = b_color + (g_color * 0x100) + (r_color * 0x10000);
		}
	}

	// ...
	{
		int y_offset = 20;
		int ws = rc.right - rc.left;
		int hs = rc.bottom - rc.top;

		int sx = 35;
		int	ex = ws - 35;
		int sy = 130;
		int ey = hs - 50;

		mArea__Chart_XY.left   = sx;
		mArea__Chart_XY.right  = ex;
		mArea__Chart_XY.top    = sy;
		mArea__Chart_XY.bottom = ey;
	}
}
void CDlg__Lot_Process::_Make__Proc_Chart()
{
	RECT rc = mArea__Chart_View;

	// ...
	int y_offset = 20;

	int ws = rc.right - rc.left;
	int hs = rc.bottom - rc.top;

	XYChart *p_xy_chart = new XYChart(ws, hs+y_offset, 0xf4f4f4, 0x000000, 1);
	p_xy_chart->setRoundedFrame(_getDefaultBgColor());

	// ...
	{
		int sx = mArea__Chart_XY.left;
		int ex = mArea__Chart_XY.right;
		int sy = mArea__Chart_XY.top;
		int ey = mArea__Chart_XY.bottom;

		p_xy_chart->setPlotArea(sx,sy, ex-sx,ey-sy, 0xffffff, -1, -1, 0xcccccc, 0xcccccc);
		p_xy_chart->setClipping();
	}

	// ...
	{
		int xs = mArea__Chart_XY.right - mArea__Chart_XY.left;	

		LegendBox *b;

		if(bActive__Chart_Single)
			b = p_xy_chart->addLegend2(30, 10, 1, "arialbd.ttf", 9);
		else
			b = p_xy_chart->addLegend2(30, 10, 10, "arialbd.ttf", 9);

		b->setBackground(Chart::Transparent, Chart::Transparent);
		b->setWidth(xs);

		//
		char str_title[256];
		strcpy(str_title, sPara__Y_Axis_Title);

		p_xy_chart->yAxis()->setTitle(str_title, "arialbd.ttf", 10);
	}

	p_xy_chart->xAxis()->setTickDensity(75, 15);

	p_xy_chart->xAxis()->setWidth(1);
	p_xy_chart->yAxis()->setWidth(1);

	// ...
	LineLayer *p_layer = p_xy_chart->addLineLayer();
	p_layer->setUseYAxis2();

	CString md_name = _Get__MDx_Name();

	int x_size = mSlot_Step.Get__Max_Step_Size_Of_MDx(md_name);
	if(x_size > 0)
	{
		char** p_x_pos; 
		p_x_pos = (char**) calloc(x_size, sizeof(char*));

		for(int c=0; c < x_size; c++)
		{
			p_x_pos[c] = (char*) calloc(20, sizeof(char));

			sprintf(p_x_pos[c], "%1d_step", c);
		}

		p_xy_chart->xAxis()->setLabels(StringArray(p_x_pos, x_size));
		// p_xy_chart->xAxis()->setLabelStep(2, 1);

		for(int c=0; c<x_size; c++)			free(p_x_pos[c]);
		free(p_x_pos);
	}

	if(bActive__Chart_Single)
	{
		int r_index = _Get__Selected_Index_Of_Slot_List();

		if(r_index >= 0)
		{
			CString str_id = _Get__ID_Of_Slot_List(r_index);

			CLS__MDx_Step_Info* p_md_db = mSlot_Step.Get_Addr__Step_Size_Of_MDx(str_id, md_name);
			if(p_md_db != NULL)
			{
				int db_size = p_md_db->sList__Step_Time.GetSize();;
				if(db_size > 0)
				{
					double* p_data__y = new double[db_size];

					COLORREF y_color = cPara__Single_Color;
					// COLORREF y_color = cPara__Slot_Color_ARGB[r_index];
					CString y_name = str_id;

					for(int i=0; i<db_size; i++)
					{
						p_data__y[i] = (double) atof(p_md_db->sList__Step_Time[i]);
					}

					p_layer->addDataSet(DoubleArray(p_data__y, db_size), y_color,y_name);
	
					delete [] p_data__y;
				}
			}
		}
	}
	else
	{
		CListCtrl* p_table = &mList__Slot_Info;

		int y_limit = p_table->GetItemCount();
		if(y_limit > _CFG__SLOT_MAX)		y_limit = _CFG__SLOT_MAX;

		for(int y=0; y<y_limit; y++)
		{
			if(p_table->GetCheck(y) < 1)		continue;

			// ...
			CString str_id = _Get__ID_Of_Slot_List(y);

			CLS__MDx_Step_Info* p_md_db = mSlot_Step.Get_Addr__Step_Size_Of_MDx(str_id, md_name);
			if(p_md_db != NULL)
			{
				int db_size = p_md_db->sList__Step_Time.GetSize();
				if(db_size > 0)
				{
					double* p_data__y = new double[db_size];

					CString  y_name = str_id;
					COLORREF y_color = cPara__Slot_Color_ARGB[y];

					for(int i=0; i<db_size; i++)
					{
						p_data__y[i] = (double) atof(p_md_db->sList__Step_Time[i]);
					}

					p_layer->addDataSet(DoubleArray(p_data__y, db_size), y_color,y_name);

					delete [] p_data__y;
				}	
			}
		}
	}

	// ...
	{
		char str_title[256];
		strcpy(str_title, sPara__X_Axis_Title);

		p_xy_chart->xAxis()->setTitle(str_title);
	}

	_trackLineLegend(p_xy_chart, mChart_Viwer.isMouseOnPlotArea() ?  mChart_Viwer.getPlotAreaMouseX() : p_xy_chart->getPlotArea()->getRightX());

	delete mChart_Viwer.getChart();
	mChart_Viwer.setChart(p_xy_chart); 	
}
int CDlg__Lot_Process::_getDefaultBgColor()
{
	LOGBRUSH LogBrush; 
	HBRUSH hBrush = (HBRUSH)SendMessage(WM_CTLCOLORDLG, (WPARAM)CClientDC(this).m_hDC, (LPARAM)m_hWnd); 

	::GetObject(hBrush, sizeof(LOGBRUSH), &LogBrush); 
	int ret = LogBrush.lbColor;

	return ((ret & 0xff) << 16) | (ret & 0xff00) | ((ret & 0xff0000) >> 16);
}

void CDlg__Lot_Process::OnMouseMovePlotArea()
{
	_trackLineLegend((XYChart *) mChart_Viwer.getChart(), mChart_Viwer.getPlotAreaMouseX()); 

	mChart_Viwer.updateDisplay();
}
void CDlg__Lot_Process::_trackLineLegend(XYChart *c, int mouseX)
{
	int check_count = _Get__Checked_Count_Of_Slot_List();

    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

    // Get the data x-value that is nearest to the mouse, and find its pixel coordinate.
    double xValue = c->getNearestXValue(mouseX);
    int xCoor = c->getXCoor(xValue);

    // Draw a vertical track line at the x-position
    d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, d->dashLineColor(0x000000, 0x0101));

    // Container to hold the legend entries
	vector<string> legendEntries;

    // Iterate through all layers to build the legend array
    for (int i = 0; i < c->getLayerCount(); ++i) 
	{
        Layer *layer = c->getLayerByZ(i);

        // The data array index of the x-value
        int xIndex = layer->getXIndexOf(xValue);

        // Iterate through all the data sets in the layer
        for (int j = 0; j < layer->getDataSetCount(); ++j) 
		{
            DataSet *dataSet = layer->getDataSetByZ(j);

            // We are only interested in visible data sets with names
            const char *dataName = dataSet->getDataName();
            int color = dataSet->getDataColor();

			if (dataName && *dataName && (color != Chart::Transparent)) 
			{
                // Build the legend entry, consist of the legend icon, name and data value.
                double dataValue = dataSet->getValue(xIndex);
				ostringstream legendEntry;

				if((bActive__Chart_Single)
				|| (check_count < 4))
				{
					/*
					CString str_comment = mSlot_Tack.Get__Slot_Comment(dataName, xIndex);

					char str_name[256];
					sprintf(str_name, "%s [%s]", dataName,str_comment);

					legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << str_name << ": " <<
						((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
					*/
					//  << "<*/*>";

					legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << dataName << ": " <<
						((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
						<< "<*/*>";
				}
				else
				{
					legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << dataName << ": " <<
						((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
						<< "<*/*>";
				}

				legendEntries.push_back(legendEntry.str());

                // Draw a track dot for data points within the plot area
                int yCoor = c->getYCoor(dataSet->getPosition(xIndex), dataSet->getUseYAxis());
                if ((yCoor >= plotArea->getTopY()) && (yCoor <= plotArea->getBottomY())) 
				{
                    d->circle(xCoor, yCoor, 4, 4, color, color);
                }
            }
        }
    }

    // Create the legend by joining the legend entries
	ostringstream legendText;
	legendText << "<*block,maxWidth=" << plotArea->getWidth() << "*><*block*><*font=arialbd.ttf*>[ "
		<< c->xAxis()->getFormattedLabel(xValue, "%1d") << " ]<*/*>";
	
	for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
		legendText << "        " << legendEntries[i];
	
    // Display the legend on the top of the plot area
    TTFText *t = d->text(legendText.str().c_str(), "arial.ttf", 8);
	t->draw(plotArea->getLeftX() + 5, plotArea->getTopY() - 3, 0x000000, Chart::BottomLeft);
	t->destroy();
}

