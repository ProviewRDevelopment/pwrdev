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

package jpwr.jop;
import java.awt.*;
import java.awt.geom.*;
import java.awt.image.*;
import java.awt.font.*;
import javax.swing.*;
import java.awt.event.*;
import jpwr.rt.*;

/**
   Jop axis arc component.
*/
public class JopAxisarc extends JComponent {
  static final long serialVersionUID = -5471079760952019966L;
  Dimension size;
  public JopAxisarc()
  {
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  private void jbInit() throws Exception {
    size = new Dimension( 102, 36);
  }
  float angle1 = 0;
  float angle2 = 360;
  int fillColor = 9999;
  int borderColor = 9999;
  public int originalTextColor = 9999;
  public int textColor = 9999;
  int lineWidth = 1;
  float lineLength;
  int lines = 11;
  int longQuotient = 1;
  int valueQuotient = 1;
  int textCnt = 0;
  GeCFormat	cFormat;
  Font font;
  public void setAngle1( float angle1) {
    this.angle1 = angle1;
  }
  public void setAngle2( float angle2) {
    this.angle2 = angle2;
  }
  public void setFillColor( int fillColor) {
    this.fillColor = fillColor;
  }
  public int getFillColor() {
    return fillColor;
  }
  public void setBorderColor( int borderColor) {
    this.borderColor = borderColor;
  }
  public int getBorderColor() {
    return borderColor;
  }
  public void setTextColor( int textColor) {
    this.textColor = textColor;
    this.originalTextColor = textColor;
  }
  public int getTextColor() {
    return textColor;
  }
  public void setLineWidth( int lineWidth) {
    this.lineWidth = lineWidth;
  }
  public int getLineWidth() {
    return lineWidth;
  }
  public void setLineLength( float lineLength) {
    this.lineLength = lineLength;
  }
  public float getLineLength() {
    return lineLength;
  }
  public void setLines( int lines) {
    this.lines = lines;
  }
  public int getLines() {
    return lines;
  }
  public void setLongQuotient( int longQuotient) {
    this.longQuotient = longQuotient;
  }
  public int getLongQuotient() {
    return longQuotient;
  }
  public void setValueQuotient( int valueQuotient) {
    this.valueQuotient = valueQuotient;
  }
  public int getValueQuotient() {
    return valueQuotient;
  }
  public void setFormat( String format) {
    this.cFormat = new GeCFormat(format);
  }
  public void setFont( Font font) {
    this.font = font;
  }
  public Font getFont() {
    return font;
  }
  public double rotate;
  public void setRotate( double rotate) { this.rotate = rotate;}
  public double getRotate() { return rotate;}
  Shape[] shapes = null;
  Line2D.Float[] hLines;
  public void paint(Graphics g1) {
    super.paint(g1);
    Graphics2D g = (Graphics2D) g1;
    Component c;
    Point p;
    paintComponent(g);
    for ( int i = 0; i < getComponentCount(); i++) {
      AffineTransform save = g.getTransform();
      c = getComponent(i);
      p = c.getLocation();
      g.translate((int)p.getX(), (int)p.getY());
      c.paint(g);
      g.setTransform(save);
    }
  }

  float hTextPosX[];
  float hTextPosY[];
  String hText[];
  float oldWidth;
  float widthOrig = 0;
  public void paintComponent(Graphics g1) {
    int i, j;
    Graphics2D g = (Graphics2D) g1;
    float width = getWidth();
    float height = getHeight();
    AffineTransform save = g.getTransform();
    float delta;
    float value;
    boolean drawText = (minValue != maxValue);

    if ( widthOrig == 0)
      widthOrig = width;

    //g.setFont( font);
    g.setFont( font.deriveFont( width / widthOrig * font.getSize()));

    if ( shapes == null || width != oldWidth) {
      float lineLen = this.lineLength * width / widthOrig;
      shapes = new Shape[1];
      FontRenderContext frc = g.getFontRenderContext();

      textCnt = 0;
      if ( lines > 0)
      {
        hLines = new Line2D.Float[lines];
	if ( drawText) {
          hText = new String[lines/valueQuotient + 1];
          hTextPosY = new float[lines/valueQuotient + 1];
          hTextPosX = new float[lines/valueQuotient + 1];
	}

	
	shapes[0] = new Arc2D.Float( 0F, 0F, width, height, angle1, angle2, Arc2D.OPEN);
	float line_angle = angle2 / (lines - 1);
	for ( i = 0; i < lines; i++) {
	  float sin1 = (float) Math.sin( (angle1 + i * line_angle) / 180 * Math.PI);
	  float cos1 = (float) Math.cos( (angle1 + i * line_angle) / 180 * Math.PI);
	  float x1, y1, x2, y2, xt, yt;

	  xt = yt = 0;
	  y1 = height / 2 * ( -sin1 + 1);
	  x1 = width / 2 * ( cos1 + 1);
	  if ( i % longQuotient == 0) {
	    y2 = height / 2 * ( -sin1 * ( 1F - lineLen) + 1);
	    x2 = width / 2 * ( cos1 * ( 1F - lineLen) + 1);
	  }
	  else {
	    y2 = height / 2 * ( -sin1 * ( 1F - lineLen / 2) + 1);
	    x2 = width / 2 * ( cos1 * ( 1F - lineLen / 2) + 1);
	  }
	  hLines[i] = new Line2D.Float( x1, y1, x2, y2);

	  if ( drawText && i % valueQuotient == 0) {
	    value = minValue + (maxValue - minValue) / ( lines - 1) * i;
		// if ( maxValue > minValue)
		//  value = maxValue - (maxValue - minValue) / ( lines - 1) * i;
		// else
		//  value = (minValue - maxValue) / ( lines - 1) * i;
	    hText[i/valueQuotient] = 
		cFormat.format( value, new StringBuffer()).toString();
	    Rectangle2D textBounds = 
		g.getFont().getStringBounds( hText[i/valueQuotient], frc);
	    float textHeight = (float) textBounds.getHeight();
	    float textWidth = (float) textBounds.getWidth();
	    yt = height / 2 * ( -sin1 * (1F - lineLen) + 1) + sin1 * textHeight;
	    xt = width / 2 * ( cos1 * (1F - lineLen) + 1) - cos1 * textWidth / 2;
	    float increment = (maxValue - minValue) / (lines - 1);
	    
	    if ( i % valueQuotient == 0 &&
		 !(angle2 == 360 && 
		   ((increment > 0 && i == lines - 1) || (increment < 0 && i == 0)))) {
		  
	      if ( i == lines - 1 && angle1 == 0 && angle2 == 180) {
		xt = xt - textWidth/2;
	      }
	      else if ( i == 0 && angle1 == 0 && angle2 != 360) {
		xt = xt - textWidth/2;
	      }
	      else {
		yt = yt + textHeight/2;
		xt = xt - textWidth/2;
	      }
	      hTextPosY[textCnt] = yt;
	      hTextPosX[textCnt] = xt;
	      textCnt++;
	    }
	  }
	}
      }
    }
    g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);

    g.setStroke( new BasicStroke((float)lineWidth));
    g.setColor(GeColor.getColor(0, borderColor));
    g.draw( shapes[0]);
    for ( i = 0; i < lines; i++)
      g.draw( hLines[i]);
    if ( drawText) {
      for ( i = 0; i < textCnt; i++) {
	g.drawString( hText[i], hTextPosX[i], hTextPosY[i]);
      } 
    }
    oldWidth = width;
  }
  public Dimension getPreferredSize() { return size;}
  public Dimension getMinimumSize() { return size;}
  float minValue = 0;
  float maxValue = 100;
  public void setMinValue( float minValue) {
    this.minValue = minValue;
  }
  public void setMaxValue( float maxValue) {
    this.maxValue = maxValue;
  }
  public float getMaxValue() {
    return maxValue;
  }
  public float getMinValue() {
    return minValue;
  }
}








