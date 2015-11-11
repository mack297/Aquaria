/*
Copyright (C) 2007, 2010 - Bit-Blot

This file is part of Aquaria.

Aquaria is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#ifndef BITMAPFONT_H
#define BITMAPFONT_H

//#include "DrawText.h"
#include "RenderObject.h"
#include "BaseText.h"

#include "../ExternalLibs/glfont2/glfont2.h"

enum BitmapFontEffect
{
	BFE_NONE			= 0,
	BFE_SHADOWBLUR		= 1,
	BFE_MAX
};

struct BmpFont
{
	BmpFont();
	~BmpFont();
	void load(const std::string &file, float scale=1, bool loadTexture=true);
	void destroy();

	glfont::GLFont font;
	float scale;
	bool loaded;

	Vector fontTopColor;
	Vector fontBtmColor;

	CountedPtr<Texture> overrideTexture;
};

class BitmapText : public BaseText
{
public:
	BitmapText(BmpFont *bmpFont);
	void setText(const std::string &text);
	void setWidth(float width);
	float getSetWidth(); // get the width that was set
	void scrollText(const std::string &text, float scrollSpeed);
	void setFontSize(float sz);
	bool isScrollingText();
	void stopScrollingText();
	bool isEmpty();
	virtual void setAlign(Align align);
	std::string getText();
	int getWidthOnScreen();
	void loadSpacingMap(const std::string &file);
	Vector getColorIndex(int i, int j);
	void updateWordColoring();
	void autoKern();
	void setBitmapFontEffect(BitmapFontEffect bfe);
	void render();
	virtual float getHeight();
	void unloadDevice();
	void reloadDevice();
	float getStringWidth(const std::string& text);
	float getActualWidth() { return maxW; }

	int getNumLines();
protected:
	float scrollSpeed;
	BmpFont *bmpFont;
	int bfePass;
	BitmapFontEffect bfe;
	void onUpdate(float dt);
	float scrollDelay;
	bool scrolling;
	int currentScrollLine;
	int currentScrollChar;
	Align align;
	float alignWidth;
	typedef std::map<char, float> SpacingMap;
	SpacingMap spacingMap;
	void formatText();
	float fontDrawSize;
	void onRender();
	typedef std::vector<std::string> Lines;
	Lines lines;
	typedef std::vector<Vector> ColorIndices;
	std::vector<ColorIndices> colorIndices;
	std::string text;
	float textWidth;
	float maxW;
};

#endif
