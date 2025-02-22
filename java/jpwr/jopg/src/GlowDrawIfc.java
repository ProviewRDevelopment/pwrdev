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
import java.awt.*;

public interface GlowDrawIfc {

    public void rect(int border, int fill, double x, double y, double witdh, double height);
    public void rect(int x, int y, int width, int height, int gc_type, int idx, int highlight);
    public void fill_rect(int x, int y, int width, int height, int gc_type);
    public void gradient_fill_rect(int x, int y, int width, int height, int gc_type, int f1, int f2, int gradient);
    public void gradient_fill_rectrounded(int x, int y, int width, int height, int amount, int gc_type, int f1, int f2, int gradient);
    public void arc(int x, int y, int width, int height, int angle1, int angle2, int gc_type, int idx, int highlight);
    public void fill_arc(int x, int y, int width, int height, int angle1, int angle2, int gc_type);
    public void gradient_fill_arc(int x, int y, int width, int height, int angle1, int angle2, int gc_type, int f1, int f2, int gradient);
    public void line(int x1, int y1, int x2, int y2, int gc_type, int idx, int highlight);
    public void line_dashed(int x1, int y1, int x2, int y2, int gc_type, int idx, int highlight, int line_type);
    public void polyline(GlowPointX[] points, int point_cnt, int gc_type, int idx, int highlight);
    public void fill_polyline(GlowPointX[] points, int point_cnt, int gc_type, int highlight);
    public void gradient_fill_polyline(GlowPointX[] points, int point_cnt, int gc_type, int f1, int f2, int gradient);
    public void text( int x, int y, String text, int gc_type, int color, int idx, int highlight, int line, 
		      int font_idx, double size, int rot);
    public  int gradient_rotate(double rotate, int gradient);
    public GlowDimension getTextExtent( String text, int idx, int type, int gc_type);
    public Color getColor(int gc_type);
    public int set_clip_rectangle( int x1, int y1, int x2, int y2);
    public void reset_clip_rectangle();
    public void push_customcolors( GlowCustomColors cc);
    public void pop_customcolors();
}
