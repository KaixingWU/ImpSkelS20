//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window* m_mainWindow;
	Fl_Menu_Bar* m_menubar;

	PaintView* m_paintView;
	OriginalView* m_origView;

	// for brush dialog
	Fl_Window* m_brushDialog;
	Fl_Choice* m_BrushTypeChoice;
	Fl_Choice* m_StrokeDirectionTypeChoice;

	Fl_Slider* m_BrushSizeSlider;
	Fl_Slider* m_BrushLineWidthSlider;
	Fl_Slider* m_BrushLineAngleSlider;
	Fl_Slider* m_BrushAlphaSlider;
	Fl_Slider* m_BrushSpacingSlider;
	Fl_Slider* m_BrushEdgeSlider;

	Fl_Group* m_SpacingGroup;
	Fl_Group* m_EdgeGroup;

	Fl_Button* m_ClearCanvasButton;
	Fl_Light_Button* m_EdgeClippingButton;
	Fl_Light_Button* m_AnotherGradientButton;
	Fl_Light_Button* m_SizeRandButton;
	Fl_Button* m_PaintButton;
	Fl_Button* m_DoitButton;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	int					getLineWidth();
	int					getLineAngle();
	void				setSize(int size);
	int					getAlpha();
	void				setAlpha(int alpha);

	double				getColorR();
	double				getColorG();
	double				getColorB();
	void				setColorR(double R);
	void				setColorG(double G);
	void				setColorB(double B);

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_nLineWidth;
	int		m_nLineAngle;
	double	m_nAlpha;
	double	m_nColorR;
	double  m_nColorG;
	double  m_nColorB;
	bool	m_bEdgeClipping;
	int		m_nEdgeThreshold;
	int		m_nAutoSpace;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		strokeDirectionTypeMenu[NUM_STROKE_TYPE + 1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void cb_colors(Fl_Menu_* o, void* v);
	static void cb_paintly(Fl_Menu_* o, void* v);
	static void cb_load_another_image(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_StrokeDirectionChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_Edge_Clipping_button(Fl_Widget* o, void* v);
	static void	cb_Another_Gradient_button(Fl_Widget* o, void* v);
	static void	cb_Size_Rand_button(Fl_Widget* o, void* v);
	static void	cb_Paint_button(Fl_Widget* o, void* v);
	static void	cb_Do_it_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void cb_lineWidthSlides(Fl_Widget* o, void* v);
	static void cb_lineAngleSlides(Fl_Widget* o, void* v);
	static void cb_alphaSlides(Fl_Widget* o, void* v);
	static void cb_color_chooser(Fl_Widget* o, void* v);
	
};

#endif
