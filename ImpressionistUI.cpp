//
// impressionistUI.h
//
// The user interface part for the program.
//

#include <FL/Fl_Color_Chooser.H>
#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}


//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}



//choose colors freely
//Called by the UI when the colors menu item is chosen
//
void ImpressionistUI::cb_colors(Fl_Menu_* o, void* v)
{
	whoami(o)->m_colorDialog->show();
}

//choose artist styles freely
//Called by the UI when the paintly menu item is chosen
//
void ImpressionistUI::cb_paintly(Fl_Menu_* o, void* v)
{

}

void ImpressionistUI::cb_load_another_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadAnotherImage(newfile);
	}
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}



//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;


	pDoc->setBrushType(type);
}

void ImpressionistUI::cb_StrokeDirectionChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)v;
	
	pDoc->m_pDirectionType = type;
}



//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


void ImpressionistUI::cb_Edge_Clipping_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

void	ImpressionistUI::cb_Another_Gradient_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

void	ImpressionistUI::cb_Size_Rand_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

void	ImpressionistUI::cb_Paint_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	pUI->m_paintView->autoDraw();
	pDoc->autoPaint();
}

void	ImpressionistUI::cb_autoSpaceRand(Fl_Widget* o, void* v) {
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->m_nRandSpaceOnOff += 1;
}

void	ImpressionistUI::cb_Do_it_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}

//updates the brush line width to use from the value of the line width slider
//called by the UI when the line width slider is moved
void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth = int(((Fl_Slider*)o)->value());
}

//updates the brush line angle to use from the value of the line angle slider
//called by the UI when the line angle slider is moved
void ImpressionistUI::cb_lineAngleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineAngle = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_autoSpaceSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAutoSpace = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	double value = ((Fl_Slider*)o)->value();
	int res1 = (int)(value * 255);
	((ImpressionistUI*)(o->user_data()))->m_nAlpha = res1;
}

void ImpressionistUI::cb_thresholdSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nEdgeThreshold = int(((Fl_Slider*)o)->value());
}

//Color choice
void ImpressionistUI::cb_color_chooser(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nColorR = ((Fl_Color_Chooser*)o)->r();
	((ImpressionistUI*)(o->user_data()))->m_nColorG = ((Fl_Color_Chooser*)o)->g();
	((ImpressionistUI*)(o->user_data()))->m_nColorB = ((Fl_Color_Chooser*)o)->b();
}

//Customize Filter

void ImpressionistUI::cb_filter_size(Fl_Menu_* o, void* v)
{
	whoami(o)->m_filterWindow->show();
}
void ImpressionistUI::cb_filter_check_size(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = (ImpressionistUI*)o->user_data();
	int w = atoi((pUI->m_filterWidth->value()));
	int h = atoi((pUI->m_filterHeight->value()));
	w = w > 1 ? w : 1;
	h = h > 1 ? h : 1;
	pUI->ShowFilterEntryValue(w, h);
	pUI->m_filterWindow->hide();
}

void ImpressionistUI::cb_applyFilter(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = (ImpressionistUI*)o->user_data();
	double* kernel = new double[pUI->m_nKernelH * pUI->m_nKernelW];
	for (int i = 0; i < pUI->m_nKernelH; ++i)
	{
		for (int j = 0; j < pUI->m_nKernelW; ++j)
		{
			int pixel = i * pUI->m_nKernelW + j;
			double weight = atof(pUI->m_EntryInputs[pixel]->value());
			//cout << weight << endl;
			kernel[pixel] = weight;
		}
	}

	pUI->getDocument()->applyCustomFilter(kernel, pUI->m_nKernelW, pUI->m_nKernelH);
	pUI->m_paintView->refresh();

}

void ImpressionistUI::ShowFilterEntryValue(int width, int height)
{
		int dialog_w = width * 30 + (width + 1) * 10 + 20;
		int dialog_h = height * 20 + (height + 1) * 10 + 40;
		m_filterEntryValueWindow = new Fl_Window(dialog_w, dialog_h, "Filter Entry Value");
		m_filterEntryValueWindow->user_data((void*)(this));
		for (int i = 1; i <= height; ++i)
		{
			for (int j = 1; j <= width; ++j)
			{
				Fl_Float_Input* input = new Fl_Float_Input(j * 10 + (j - 1) * 30, i * 10 + (i - 1) * 20, 30, 20, "");
				input->value("1.0");
				m_EntryInputs.push_back(input);
			}
		}


		m_filterApply = new Fl_Button(dialog_w / 2 , dialog_h - 30, 40, 20, "Apply");
		m_filterApply->user_data((void*)(this));
		m_filterApply->callback(cb_applyFilter);


		m_filterEntryValueWindow->end();
		m_filterEntryValueWindow->show();
		m_nKernelH = height;
		m_nKernelW = width;

};


//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//Return the brush line width
int ImpressionistUI::getLineWidth()
{
	return m_nLineWidth;
}

//Return the brush line angle
int ImpressionistUI::getLineAngle()
{
	return m_nLineAngle;
}

double ImpressionistUI::getAlpha()
{
	return m_nAlpha;
}

double ImpressionistUI::getColorR()
{
	return m_nColorR;
}

double ImpressionistUI::getColorG()
{
	return m_nColorG;
}

double ImpressionistUI::getColorB()
{
	return m_nColorB;
}

int ImpressionistUI::getAutoSpace() {
	return m_nAutoSpace;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}

void ImpressionistUI::setLineAngle(int angle) {
	m_nLineAngle = angle;

	if (angle<360) {
		m_BrushLineAngleSlider->value(m_nLineAngle);
	}
}

void ImpressionistUI::setColorR(double R)
{
	m_nColorR = R;
}

void ImpressionistUI::setColorG(double G)
{
	m_nColorG = G;
}

void ImpressionistUI::setColorB(double B)
{
	m_nColorB = B;
}

void ImpressionistUI::setAlpha(double alpha) 
{
	m_nAlpha = alpha;
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback*)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback*)ImpressionistUI::cb_brushes },
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback*)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },

		{ "&Colors",       FL_ALT + 'k', (Fl_Callback*)ImpressionistUI::cb_colors},
		{ "&Paintly",      FL_ALT + 'p', (Fl_Callback*)ImpressionistUI::cb_paintly, 0, FL_MENU_DIVIDER},
		{ "&Define Filter", FL_ALT + 'e', (Fl_Callback*)ImpressionistUI::cb_filter_size, 0, FL_MENU_DIVIDER},
		{ "&Load another image", FL_ALT + 'a', (Fl_Callback*)ImpressionistUI::cb_load_another_image, 0, FL_MENU_DIVIDER},

		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
   {"Stars",			FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_STAR},
   {"Filter Blur",			FL_ALT + 'b', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_BLUR_FILTER},
  {0}
};

//Stroke Direction menu definition
Fl_Menu_Item ImpressionistUI::strokeDirectionTypeMenu[NUM_STROKE_TYPE + 1] = {
  {"Slider/Right Mouse",			FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_StrokeDirectionChoice, (void*)SLIDER_RIGHT_MOUSE},
  {"Gradient",				FL_ALT + 'g', (Fl_Callback*)ImpressionistUI::cb_StrokeDirectionChoice, (void*)GRADIENT},
  {"Brush Direction",			FL_ALT + 'b', (Fl_Callback*)ImpressionistUI::cb_StrokeDirectionChoice, (void*)BRUSH_DIRECTION},
  {0}
};



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_nLineWidth = 1;
	m_nLineAngle = 0;
	m_nAlpha = 255;
	m_nColorR = 1.00;
	m_nColorG = 1.00;
	m_nColorB = 1.00;
	m_nAutoSpace = 1;



	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");

	
	// Add a brush type choice to the dialog
	m_BrushTypeChoice = new Fl_Choice(50, 10, 150, 25, "&Brush");
	m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushTypeChoice->menu(brushTypeMenu);
	m_BrushTypeChoice->callback(cb_brushChoice);

	// Add a Stroke Direction type choice to the dialog
	m_StrokeDirectionTypeChoice = new Fl_Choice(120, 40, 150, 25, "&Stroke Direction");
	m_StrokeDirectionTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
	m_StrokeDirectionTypeChoice->menu(strokeDirectionTypeMenu);
	m_StrokeDirectionTypeChoice->callback(cb_StrokeDirectionChoice);
	m_StrokeDirectionTypeChoice->deactivate();

	//Add Group
	/*m_SpacingGroup = new Fl_Group(10, 250, 300, 30);
	m_SpacingGroup->add(m_BrushSpacingSlider);
	m_SpacingGroup->add(m_SizeRandButton);
	m_SpacingGroup->add(m_PaintButton);
	m_SpacingGroup->end();


	m_EdgeGroup = new Fl_Group(10, 250, 300, 30);
	m_EdgeGroup->add(m_BrushEdgeSlider);
	m_EdgeGroup->add(m_DoitButton);
	m_EdgeGroup->end();
	*/

	//Add a Clear Canvas Button to the dialog
	m_ClearCanvasButton = new Fl_Button(240, 10, 150, 25, "&Clear Canvas");
	m_ClearCanvasButton->user_data((void*)(this));
	m_ClearCanvasButton->callback(cb_clear_canvas_button);

	//Add a Edge Clipping Button to the dialog
	m_EdgeClippingButton = new Fl_Light_Button(10, 205, 110, 25, "&Edge Clipping");
	m_EdgeClippingButton->user_data((void*)(this));
	m_EdgeClippingButton->callback(cb_clear_canvas_button);

	//Add a Another Gradient Button to the dialog
	m_AnotherGradientButton = new Fl_Light_Button(250, 205, 140, 25, "&Another Gradient");
	m_AnotherGradientButton->user_data((void*)(this));
	m_AnotherGradientButton->callback(cb_clear_canvas_button);

	//Add a Size Rand Button to the dialog
	m_SizeRandButton = new Fl_Light_Button(230, 250, 85, 21, "&Size Rand");
	m_SizeRandButton->user_data((void*)(this));
	m_SizeRandButton->callback(cb_autoSpaceRand);

	//Add a Paint Button to the dialog
	m_PaintButton = new Fl_Button(340, 250, 50, 21, "&Paint");
	m_PaintButton->user_data((void*)(this));
	m_PaintButton->callback(cb_Paint_button);

	//Add a Do it Button to the dialog
	m_DoitButton = new Fl_Button(340, 290, 50, 21, "&Do it");
	m_DoitButton->user_data((void*)(this));
	m_DoitButton->callback(cb_clear_canvas_button);

	// Add brush size slider to the dialog 
	m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
	m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushSizeSlider->labelfont(FL_COURIER);
	m_BrushSizeSlider->labelsize(12);
	m_BrushSizeSlider->minimum(1);
	m_BrushSizeSlider->maximum(40);
	m_BrushSizeSlider->step(1);
	m_BrushSizeSlider->value(m_nSize);
	m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
	m_BrushSizeSlider->callback(cb_sizeSlides);

	// Add brush line width slider to the dialog
	m_BrushLineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
	m_BrushLineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushLineWidthSlider->type(FL_HOR_NICE_SLIDER); //the button
	m_BrushLineWidthSlider->labelfont(FL_COURIER); //type of letters
	m_BrushLineWidthSlider->labelsize(12);
	m_BrushLineWidthSlider->minimum(1);
	m_BrushLineWidthSlider->maximum(40);
	m_BrushLineWidthSlider->step(1); // value change each step
	m_BrushLineWidthSlider->value(m_nLineWidth);//line width
	m_BrushLineWidthSlider->align(FL_ALIGN_RIGHT);
	m_BrushLineWidthSlider->callback(cb_lineWidthSlides);
	m_BrushLineWidthSlider->deactivate();

	// Add brush line angle slider to the dialog
	m_BrushLineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
	m_BrushLineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushLineAngleSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushLineAngleSlider->labelfont(FL_COURIER);
	m_BrushLineAngleSlider->labelsize(12);
	m_BrushLineAngleSlider->minimum(0);
	m_BrushLineAngleSlider->maximum(359);
	m_BrushLineAngleSlider->step(1);
	m_BrushLineAngleSlider->value(m_nLineAngle);//line angle
	m_BrushLineAngleSlider->align(FL_ALIGN_RIGHT);
	m_BrushLineAngleSlider->callback(cb_lineAngleSlides);
	m_BrushLineAngleSlider->deactivate();

	// Add brush alpha slider to the dialog
	m_BrushAlphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
	m_BrushAlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushAlphaSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushAlphaSlider->labelfont(FL_COURIER);
	m_BrushAlphaSlider->labelsize(12);
	m_BrushAlphaSlider->minimum(0.00);
	m_BrushAlphaSlider->maximum(1.00);
	m_BrushAlphaSlider->step(0.01);
	m_BrushAlphaSlider->value(1);
	m_BrushAlphaSlider->align(FL_ALIGN_RIGHT);
	m_BrushAlphaSlider->callback(cb_alphaSlides);

	// Add brush spacing slider to the dialog
	m_BrushSpacingSlider = new Fl_Value_Slider(10, 250, 140, 20, "Spacing");
	m_BrushSpacingSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushSpacingSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushSpacingSlider->labelfont(FL_COURIER);
	m_BrushSpacingSlider->labelsize(12);
	m_BrushSpacingSlider->minimum(1);
	m_BrushSpacingSlider->maximum(16);
	m_BrushSpacingSlider->step(1);
	m_BrushSpacingSlider->value(m_nAutoSpace);
	m_BrushSpacingSlider->align(FL_ALIGN_RIGHT);
	m_BrushSpacingSlider->callback(cb_autoSpaceSlides);

	// Add brush edge slider to the dialog
	m_BrushEdgeSlider = new Fl_Value_Slider(10, 290, 200, 20, "Edge Threshold");
	m_BrushEdgeSlider->user_data((void*)(this));	// record self to be used by static callback functions
	m_BrushEdgeSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushEdgeSlider->labelfont(FL_COURIER);
	m_BrushEdgeSlider->labelsize(12);
	m_BrushEdgeSlider->minimum(0);
	m_BrushEdgeSlider->maximum(500);
	m_BrushEdgeSlider->step(1);
	m_BrushEdgeSlider->value(m_nEdgeThreshold);
	m_BrushEdgeSlider->align(FL_ALIGN_RIGHT);
	m_BrushEdgeSlider->callback(cb_thresholdSlides);


    m_brushDialog->end();	


	// Color dialog definition
	m_colorDialog = new Fl_Window(250, 250, "Color Selector");
	m_colorChooser = new Fl_Color_Chooser(30, 20, 200, 200, "&Color Blending");
	m_colorChooser->user_data((void*)(this));
	m_colorChooser->rgb(m_nColorR, m_nColorG, m_nColorB);
	m_colorChooser->callback(cb_color_chooser);
	m_colorDialog->end();

	m_filterWindow = new Fl_Window(300, 80, "Filter");
	m_filterWidth = new Fl_Int_Input(80, 10, 50, 20, "Width");
	m_filterWidth->labelfont(FL_COURIER);
	m_filterWidth->labelsize(12);
	m_filterWidth->value("1");
	m_filterHeight = new Fl_Int_Input(180, 10, 60, 20, "Height");
	m_filterHeight->labelfont(FL_COURIER);
	m_filterHeight->labelsize(12);
	m_filterHeight->value("1");
	m_filterCheck = new Fl_Button(120, 40, 80, 20, "&Check");
	m_filterCheck->user_data((void*)(this));
	m_filterCheck->callback(cb_filter_check_size);
	m_filterWindow->end();

}
