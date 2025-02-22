 /* 
 * ProviewR   Open Source Process Control.
 * Copyright (C) 2005-2025 SSAB EMEA AB.
 *
 * This file is part of ProviewR.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 2 of 
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with ProviewR. If not, see <http://www.gnu.org/licenses/>
 *
 * Linking ProviewR statically or dynamically with other modules is
 * making a combined work based on ProviewR. Thus, the terms and
 * conditions of the GNU General Public License cover the whole 
 * combination.
 *
 * In addition, as a special exception, the copyright holders of
 * ProviewR give you permission to, from the build function in the
 * ProviewR Configurator, combine ProviewR with modules generated by the
 * ProviewR PLC Editor to a PLC program, regardless of the license
 * terms of these modules. You may copy and distribute the resulting
 * combined work under the terms of your choice, provided that every 
 * copy of the combined work is accompanied by a complete copy of 
 * the source code of ProviewR (the version used to produce the
 * combined work), being distributed under the terms of the GNU 
 * General Public License plus this exception.
 */

package jpwr.jopg;
import jpwr.rt.*;
import java.io.*;
import java.util.*;

public class GrowArc extends GlowArrayElem {
    GrowCmn cmn;
    String n_name;
    double x_right;
    double x_left;
    double y_high;
    double y_low;
    int original_border_drawtype;
    int original_fill_drawtype;
    int fill_drawtype;
    int background_drawtype;
    int border;
    double shadow_width;
    int shadow_contrast;
    int shadow;
    int relief;
    int disable_shadow;
    int fixcolor;
    int fixposition;
    int gradient;
    int gradient_contrast;
    int disable_gradient;
    int fill_eq_background;
    int dynamicsize;
    GlowTransform trf;

    GlowPoint ll;
    GlowPoint ur;
    int draw_type;
    int angle1;
    int angle2;
    int line_width;
    int display_level;
    int fill;

    public GrowArc(GrowCmn cmn) {
	this.cmn = cmn;
	trf = new GlowTransform();
	ll = new GlowPoint();
	ur = new GlowPoint();
	background_drawtype = Glow.eDrawType_No;
    }

    public int type() {
	return Glow.eObjectType_GrowArc;
    }

    public void open(BufferedReader reader) {
	String line;
	StringTokenizer token;
	boolean end_found = false;

	try {
	    while( (line = reader.readLine()) != null) {
		token = new StringTokenizer(line);
		int key = Integer.valueOf(token.nextToken());
		if ( cmn.debug) System.out.println( "GrowArc : " + line);

		switch ( key) {
		case Glow.eSave_GrowArc: 
		    break;
		case Glow.eSave_GrowArc_n_name:
		    if ( token.hasMoreTokens())
			n_name = token.nextToken();
		    break;
		case Glow.eSave_GrowArc_x_right: 
		    x_right = new Double(token.nextToken()).doubleValue(); 
		    break;
		case Glow.eSave_GrowArc_x_left: 
		    x_left = new Double(token.nextToken()).doubleValue(); 
		    break;
		case Glow.eSave_GrowArc_y_high: 
		    y_high = new Double(token.nextToken()).doubleValue(); 
		    break;
		case Glow.eSave_GrowArc_y_low: 
		    y_low = new Double(token.nextToken()).doubleValue(); 
		    break;
		case Glow.eSave_GrowArc_original_border_drawtype: 
		    original_border_drawtype = Integer.valueOf(token.nextToken()); 
		    break;
		case Glow.eSave_GrowArc_original_fill_drawtype: 
		    original_fill_drawtype = Integer.valueOf(token.nextToken()); 
		    break;
		case Glow.eSave_GrowArc_fill_drawtype: 
		    fill_drawtype = Integer.valueOf(token.nextToken()); 
		    break;
		case Glow.eSave_GrowArc_background_drawtype: 
		    background_drawtype = Integer.valueOf(token.nextToken()); 
		    break;
		case Glow.eSave_GrowArc_border: 
		    border = Integer.valueOf(token.nextToken()); 
		    break;
		case Glow.eSave_GrowArc_shadow_width: 
		    shadow_width = new Double(token.nextToken()).doubleValue(); 
		    break;
		case Glow.eSave_GrowArc_shadow_contrast: 
		    shadow_contrast = Integer.valueOf(token.nextToken()); 
		    break;
		case Glow.eSave_GrowArc_shadow: 
		    shadow = Integer.valueOf(token.nextToken()); 
		    break;
		case Glow.eSave_GrowArc_relief: 
		    relief = Integer.valueOf(token.nextToken()); 
		    break;
		case Glow.eSave_GrowArc_disable_shadow: 
		    disable_shadow = Integer.valueOf(token.nextToken()); 
		    break;
		case Glow.eSave_GrowArc_fixcolor:
		    fixcolor = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_GrowArc_fixposition:
		    fixposition = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_GrowArc_gradient:
		    gradient = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_GrowArc_gradient_contrast:
		    gradient_contrast = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_GrowArc_disable_gradient:
		    disable_gradient = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_GrowArc_fill_eq_background:
		    fill_eq_background = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_GrowArc_dynamicsize:
		    dynamicsize = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_GrowArc_dynamic:
		    if ( cmn.dynamicsize > 0) {
			for ( int j = 0; j < cmn.dynamicsize; j++) 
			    line = reader.readLine();  // TODO handle backslash and citationmarks
		    }
		    break;
		case Glow.eSave_GrowArc_arc_part: 
		    glowarc_open( reader);
		    break;
		case Glow.eSave_GrowArc_trf: 
		    trf.open( reader); 
		    break;
		case Glow.eSave_End:
		    end_found = true;
		    break;
		default:
		    System.out.println( "Syntax error in GrowArc");
		    break;
		}
		if ( end_found)
		    break;
	    }
		
	} catch ( Exception e) {
	    System.out.println( "IOException GrowArc");
	}
    }

    public void glowarc_open(BufferedReader reader) {
	String line;
	StringTokenizer token;
	boolean end_found = false;

	try {
	    while( (line = reader.readLine()) != null) {
		token = new StringTokenizer(line);
		int key = Integer.valueOf(token.nextToken());
		if ( cmn.debug) System.out.println( "GlowArc : " + line);

		switch ( key) {

		case Glow.eSave_Arc: 
		    break;
		case Glow.eSave_Arc_draw_type: 
		    draw_type = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_Arc_angle1: 
		    angle1 = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_Arc_angle2: 
		    angle2 = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_Arc_line_width:
		    line_width = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_Arc_fill:
		    fill = Integer.valueOf(token.nextToken());
		    break;
		case Glow.eSave_Arc_ll:
		    ll.open( reader);
		    break;
		case Glow.eSave_Arc_ur:
		    ur.open( reader);
		    break;
		case Glow.eSave_End:
		    end_found = true;
		    break;
		default:
		    System.out.println( "Syntax error in GlowArc");
		    break;
		}
		if ( end_found)
		    break;

	    }

	} catch ( Exception e) {
	    System.out.println( "IOException GlowArc");
	}
    }

    public int eventHandler( GlowEvent event, double fx, double fy) {
	GlowPointDX rp;

	switch ( event.event) {
	case Glow.eEvent_CursorMotion:		
	    return 0;
	default: ;
	}

	rp = trf.reverse( fx, fy);
	//rp = new GlowPoint();
	//rp.x = fx;
	//rp.y = fy;
	if ( ll.x <= rp.x && rp.x <= ur.x &&
	     ll.y <= rp.y && rp.y <= ur.y) {
	    System.out.println( "Event handler: Hit in arc");
	    return 1;
	}  
	else
	    return 0;
    }

    public void draw() {
	draw( null, 0, 0, null, null);
    }


    public void draw(GlowTransform t, int highlight, int hot, Object node, Object colornode) {
	if ( cmn.nodraw != 0)
	    return;

	int drawtype;
	int idx;
	int chot = 0;

	if ( cmn.hot_indication == Glow.eHotIndication_No)
	    hot = 0;
	else if ( cmn.hot_indication == Glow.eHotIndication_DarkColor) {
	    chot = hot;
	    hot = 0;
	}
	else if ( cmn.hot_indication == Glow.eHotIndication_LightColor) {
	    chot = -hot;
	    hot = 0;
	}

	if ( fixcolor != 0)
	    colornode = null;

	if ( node != null && ((GrowNode)node).line_width != 0)
	    idx = (int)( cmn.mw.zoom_factor_y / cmn.mw.base_zoom_factor * 
		       ((GrowNode)node).line_width - 1);
	else
	    idx = (int)( cmn.mw.zoom_factor_y / cmn.mw.base_zoom_factor * line_width - 1);
	idx += hot;
	idx = Math.max( 0, idx);
	idx = Math.min( idx, Glow.DRAW_TYPE_SIZE-1);
	int x1, y1, x2, y2, ll_x, ll_y, ur_x, ur_y, rot;

	if ( t == null) {
	    x1 = (int)( trf.x( ll.x, ll.y) * cmn.mw.zoom_factor_x + 0.5) - cmn.mw.offset_x;
	    y1 = (int)( trf.y( ll.x, ll.y) * cmn.mw.zoom_factor_y + 0.5) - cmn.mw.offset_y;
	    x2 = (int)( trf.x( ur.x, ur.y) * cmn.mw.zoom_factor_x + 0.5) - cmn.mw.offset_x;
	    y2 = (int)( trf.y( ur.x, ur.y) * cmn.mw.zoom_factor_y + 0.5) - cmn.mw.offset_y;
	    rot = (int)( trf.rot());
	}
	else {
	    x1 = (int)( trf.x( t, ll.x, ll.y) * cmn.mw.zoom_factor_x + 0.5) - cmn.mw.offset_x;
	    y1 = (int)( trf.y( t, ll.x, ll.y) * cmn.mw.zoom_factor_y + 0.5) - cmn.mw.offset_y;
	    x2 = (int)( trf.x( t, ur.x, ur.y) * cmn.mw.zoom_factor_x + 0.5) - cmn.mw.offset_x;
	    y2 = (int)( trf.y( t, ur.x, ur.y) * cmn.mw.zoom_factor_y + 0.5) - cmn.mw.offset_y;
	    rot = (int)( trf.rot( t));
	}

	if ( rot % 90 != 0  && Math.abs((ur.x - ll.x) - (ur.y - ll.y)) < Float.MIN_VALUE) {
	    double scale;
	    double x_c;
	    double y_c;
	    if ( t == null) {
		scale = trf.vertical_scale( trf);
		x_c = ((trf.x( ll.x, ll.y) * cmn.mw.zoom_factor_x - cmn.mw.offset_x) +
		       (trf.x( ur.x, ur.y) * cmn.mw.zoom_factor_x - cmn.mw.offset_x)) / 2;
		y_c = ((trf.y( ll.x, ll.y) * cmn.mw.zoom_factor_y - cmn.mw.offset_y) +
		       (trf.y( ur.x, ur.y) * cmn.mw.zoom_factor_y - cmn.mw.offset_y)) / 2;
	    }
	    else {
		GlowTransform tmp = t.multiply( trf);
		scale = trf.vertical_scale( tmp);
		x_c = ((trf.x( t, ll.x, ll.y) * cmn.mw.zoom_factor_x - cmn.mw.offset_x) +
		       (trf.x( t, ur.x, ur.y) * cmn.mw.zoom_factor_x - cmn.mw.offset_x)) / 2;
		y_c = ((trf.y( t, ll.x, ll.y) * cmn.mw.zoom_factor_y - cmn.mw.offset_y) +
		       (trf.y( t, ur.x, ur.y) * cmn.mw.zoom_factor_y - cmn.mw.offset_y)) / 2;
	    }
    
	    x1 = (int)(-scale * ((ur.x - ll.x)/2 * cmn.mw.zoom_factor_x) + x_c + 0.5);
	    y1 = (int)(-scale * ((ur.y - ll.y)/2 * cmn.mw.zoom_factor_y) + y_c + 0.5);
	    x2 = (int)(scale * ((ur.x - ll.x)/2 * cmn.mw.zoom_factor_x) + x_c + 0.5);
	    y2 = (int)(scale * ((ur.y - ll.y)/2 * cmn.mw.zoom_factor_y) + y_c + 0.5);
	}

	ll_x = Math.min( x1, x2);
	ur_x = Math.max( x1, x2);
	ll_y = Math.min( y1, y2);
	ur_y = Math.max( y1, y2);

	if ( fill != 0) {
	    boolean display_shadow = ((node != null && ((GrowNode)node).shadow != 0) || shadow != 0) && disable_shadow == 0;
	    int fillcolor;
	    if ( fill_eq_background != 0)
		fillcolor = GlowColor.get_drawtype( background_drawtype, Glow.eDrawType_FillHighlight,
						    highlight, colornode, 3, 0);
	    else
		fillcolor = GlowColor.get_drawtype( fill_drawtype, Glow.eDrawType_FillHighlight,
						    highlight, colornode, 1, 0);

	    int grad = gradient;
	    if ( gradient == Glow.eGradient_No && 
		 (node != null && ((GrowNode)node).gradient != Glow.eGradient_No) && disable_gradient == 0)
		grad = ((GrowNode)node).gradient;
    
	    if ( !display_shadow || shadow_width == 0 || angle2 != 360) {
		if ( grad == Glow.eGradient_No || fillcolor == Glow.eDrawType_ColorRed) {
		    if ( chot != 0)
			drawtype = GlowColor.shift_drawtype( fillcolor, chot, null);
		    else
			drawtype = fillcolor;
		    cmn.gdraw.fill_arc( ll_x, ll_y, ur_x - ll_x, ur_y - ll_y,
					angle1 - rot, angle2, drawtype);
		}
		else {
		    int f1, f2;
		    if ( gradient_contrast >= 0) {
			f2 = GlowColor.shift_drawtype( fillcolor, -gradient_contrast/2 + chot, null);
			f1 = GlowColor.shift_drawtype( fillcolor, (int)((float)(gradient_contrast)/2+0.6) + chot, null);
		    }
		    else {
			f2 = GlowColor.shift_drawtype( fillcolor, -(int)((float)(gradient_contrast)/2-0.6) + chot, null);
			f1 = GlowColor.shift_drawtype( fillcolor, gradient_contrast/2 + chot, null);
		    }
		    cmn.gdraw.gradient_fill_arc( ll_x, ll_y, ur_x - ll_x, ur_y - ll_y, angle1 - rot, 
						 angle2, fillcolor, f1, f2, grad);
		}
	    }
	    else {
		int ish = (int)( shadow_width / 100 * Math.min(ur_x - ll_x, ur_y - ll_y) + 0.5);
		int drawtype_incr = shadow_contrast;
		if ( relief == Glow.eRelief_Down)
		    drawtype_incr = -shadow_contrast;

		if ( grad == Glow.eGradient_No || fillcolor == Glow.eDrawType_ColorRed) {

		    // Draw light shadow
		    drawtype = GlowColor.shift_drawtype( fillcolor, -drawtype_incr + chot, colornode);
		    
		    cmn.gdraw.fill_arc( ll_x, ll_y, ur_x - ll_x, ur_y - ll_y,
					35, 140, drawtype);

		    // Draw dark shadow
		    drawtype = GlowColor.shift_drawtype( fillcolor, drawtype_incr + chot, colornode);
		    
		    cmn.gdraw.fill_arc( ll_x, ll_y, ur_x - ll_x, ur_y - ll_y,
					215, 140, drawtype);

		    // Draw medium shadow and body
		    if ( chot != 0)
			drawtype = GlowColor.shift_drawtype( fillcolor, chot, null);
		    else 
			drawtype = fillcolor;
		    
		    cmn.gdraw.fill_arc(ll_x, ll_y, ur_x - ll_x, ur_y - ll_y,
				       -5, 40, drawtype);
		    cmn.gdraw.fill_arc(ll_x, ll_y, ur_x - ll_x, ur_y - ll_y,
				       175, 40, drawtype);
		    
		    cmn.gdraw.fill_arc(ll_x + ish, ll_y + ish, ur_x - ll_x - 2*ish, ur_y - ll_y - 2*ish,
				       angle1 - rot, angle2, drawtype);
		}
		else {
		    int f1, f2;
		    
		    // Draw shadow
		    f1 = GlowColor.shift_drawtype( fillcolor, -drawtype_incr + chot, colornode);
		    f2 = GlowColor.shift_drawtype( fillcolor, drawtype_incr + chot, colornode);

		    cmn.gdraw.gradient_fill_arc( ll_x, ll_y, ur_x - ll_x, ur_y - ll_y,
						 angle1 - rot, angle2, fillcolor, f2, f1, Glow.eGradient_DiagonalUpperLeft);

		    // Draw circle
		    if ( gradient_contrast >= 0) {
			f2 = GlowColor.shift_drawtype( fillcolor, -gradient_contrast/2 + chot, null);
			f1 = GlowColor.shift_drawtype( fillcolor, (int)((float)(gradient_contrast)/2+0.6) + chot, null);
		    }
		    else {
			f2 = GlowColor.shift_drawtype( fillcolor, -(int)((float)(gradient_contrast)/2-0.6) + chot, null);
			f1 = GlowColor.shift_drawtype( fillcolor, gradient_contrast/2 + chot, null);
		    }
		    cmn.gdraw.gradient_fill_arc( ll_x + ish, ll_y + ish, ur_x - ll_x - 2*ish, ur_y - ll_y - 2*ish,
						 angle1 - rot, angle2, fillcolor, f1, f2, grad);
		}
	    }
	}
	if ( border != 0 || fill == 0) {
	    drawtype = GlowColor.get_drawtype( draw_type, Glow.eDrawType_LineHighlight,
					       highlight, colornode, 0, 0);
	    cmn.gdraw.arc( ll_x, ll_y, ur_x - ll_x, ur_y - ll_y, 
			   angle1 - rot, angle2, drawtype, idx, 0);
	}
	
    }

    public Object getCmn() { 
	return cmn;
    }

    public String getName() {
	return n_name;
    }
}
