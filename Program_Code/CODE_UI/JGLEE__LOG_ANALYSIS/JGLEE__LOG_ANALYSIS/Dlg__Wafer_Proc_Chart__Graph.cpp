#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_Proc_Chart.h"
#include "Macro_Function.h"

#include <math.h>
#include <vector>
#include <sstream>

using namespace std;


// ...
void CDlg__Wafer_Proc_Chart::_Init__Proc_Chart()
{
	RECT rc;
	m_ChartViewer.GetClientRect(&rc);

	rc.top -= 1;
	rc.right -= 1;

	mArea__Chart_View = rc;

	// ...
	{
		int i_limit = _DEF__Y_SIZE;

		for(int i=0; i<i_limit; i++)
		{
			int g_color = 0;
			int r_color = 0;
			int b_color = 0;

				 if(i == 0)			r_color = 255;
			else if(i == 1)			g_color = 255;
			else if(i == 2)			b_color = 255;
			else if(i == 3)
			{
				r_color = 255;
				g_color = 255;
			}
			else if(i == 4)
			{
				r_color = 255;
				b_color = 255;
			}
			else if(i == 5)
			{
				g_color = 255;
				b_color = 255;
			}
			else if(i == 6)			r_color = 125;
			else if(i == 7)			g_color = 125;
			else if(i == 8)			b_color = 125;

			int rgb_color = b_color + (g_color * 0x100) + (r_color * 0x10000);
			cPara__Y_Color[i] = rgb_color;

			cList__Channel_Color_RGB[i] = RGB(r_color,g_color,b_color);
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
		int sy = 60;
		int ey = hs - 50;

		mArea__Chart_XY.left   = sx;
		mArea__Chart_XY.right  = ex;
		mArea__Chart_XY.top    = sy;
		mArea__Chart_XY.bottom = ey;
	}
}
void CDlg__Wafer_Proc_Chart::_Make__Proc_Chart()
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
	CProc_Log__XY_Data *p_xy_data = pLog_Proc->Get_Addr__Proc_XY_Data();

	LineLayer *p_layer = p_xy_chart->addLineLayer();
	p_layer->setUseYAxis2();

	// ...
	{
		int db_size = p_xy_data->Get__X_Size();

		if(db_size > 0)
		{
			double* p_x_stamp = new double [db_size + 1];
			p_xy_data->Get__X_Data(db_size, p_x_stamp);

			// ...
			double x_min = p_x_stamp[0];
			double x_max = p_x_stamp[db_size-1];
			
			p_xy_chart->xAxis()->setDateScale(0, x_max+1.0);
			// p_xy_chart->xAxis()->setLabelFormat("{value|hh:nn:ss}");

			p_layer->setXData(DoubleArray(p_x_stamp, db_size));

			delete [] p_x_stamp;
		}
	}

	if(bActive__Chart_Single)
	{
		int r_index = _Get__Selected_Index_Of_Channel_List();

		if(r_index >= 0)
		{
			CString str_id   = _Get__ID_Of_Channel_List(r_index);
			CString str_name = _Get__Name_Of_Channel_List(r_index);
			CString ch_name  = _Get__Channel_Of_Channel_List(r_index);

			CStringArray l_y_data;
			p_xy_data->Get__All_Y_Data(ch_name, l_y_data);

			int db_size = l_y_data.GetSize();
			if(db_size > 0)
			{
				double* p_data__y = new double[db_size];

				CString  y_name;
				y_name.Format("%s [%s]", str_id,str_name);

				COLORREF y_color = cPara__Single_Color;

				for(int i=0; i<db_size; i++)
				{
					p_data__y[i] = (double) atof(l_y_data[i]);
				}

				p_layer->addDataSet(DoubleArray(p_data__y, db_size), y_color,y_name);

				delete [] p_data__y;
			}
		}
	}
	else
	{
		CListCtrl* p_table = &mList__Channel_Sel;

		CStringArray l_name;
		CStringArray l_channel;

		pLog_Proc->Get__Template_Interrval(l_name,l_channel);

		int y_limit = l_channel.GetSize();
		if(y_limit > _DEF__Y_SIZE)		y_limit = _DEF__Y_SIZE;

		for(int y=0; y<y_limit; y++)
		{
			if(p_table->GetCheck(y) < 1)		continue;

			// ...
			CString ch_name = _Get__Channel_Of_Channel_List(y);

			CStringArray l_y_data;
			p_xy_data->Get__All_Y_Data(ch_name, l_y_data);

			int db_size = l_y_data.GetSize();
			if(db_size > 0)
			{
				double* p_data__y = new double[db_size];

				CString  y_name = _Get__ID_Of_Channel_List(y);
				COLORREF y_color = cPara__Y_Color[y];

				for(int i=0; i<db_size; i++)
				{
					p_data__y[i] = (double) atof(l_y_data[i]);
				}

				p_layer->addDataSet(DoubleArray(p_data__y, db_size), y_color,y_name);

				delete [] p_data__y;
			}	
		}
	}

	// ...
	{
		char str_title[256];
		strcpy(str_title, sPara__X_Axis_Title);

		p_xy_chart->xAxis()->setTitle(str_title);
	}

	_trackLineLegend(p_xy_chart, m_ChartViewer.isMouseOnPlotArea() ?  m_ChartViewer.getPlotAreaMouseX() : p_xy_chart->getPlotArea()->getRightX());

	delete m_ChartViewer.getChart();
	m_ChartViewer.setChart(p_xy_chart); 	
}
int CDlg__Wafer_Proc_Chart::_getDefaultBgColor()
{
	LOGBRUSH LogBrush; 
	HBRUSH hBrush = (HBRUSH)SendMessage(WM_CTLCOLORDLG, (WPARAM)CClientDC(this).m_hDC, (LPARAM)m_hWnd); 

	::GetObject(hBrush, sizeof(LOGBRUSH), &LogBrush); 
	int ret = LogBrush.lbColor;

	return ((ret & 0xff) << 16) | (ret & 0xff00) | ((ret & 0xff0000) >> 16);
}

void CDlg__Wafer_Proc_Chart::OnMouseMovePlotArea()
{
	_trackLineLegend((XYChart *)m_ChartViewer.getChart(), m_ChartViewer.getPlotAreaMouseX()); 
	m_ChartViewer.updateDisplay();
}
void CDlg__Wafer_Proc_Chart::_trackLineLegend(XYChart *c, int mouseX)
{
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
				
				legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << dataName << ": " <<
					((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
					<< "<*/*>";
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
	legendText << "<*block,maxWidth=" << plotArea->getWidth() << "*><*block*><*font=arialbd.ttf*>["
		<< c->xAxis()->getFormattedLabel(xValue, "%.3f") << "]<*/*>";
	//	<< c->xAxis()->getFormattedLabel(xValue, "hh:nn:ss") << "]<*/*>";
	
	for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
		legendText << "        " << legendEntries[i];
	
    // Display the legend on the top of the plot area
    TTFText *t = d->text(legendText.str().c_str(), "arial.ttf", 8);
	t->draw(plotArea->getLeftX() + 5, plotArea->getTopY() - 3, 0x000000, Chart::BottomLeft);
	t->destroy();
}

