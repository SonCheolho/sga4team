#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init(void)
{
	return S_OK;
}

void imageManager::release(void)
{
	this->deleteAll();
}

image * imageManager::addImage(string strKey, int width, int height)
{
	//추가하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	//이미지가 존재하지 않으니까 새로 생성후 초기화
	img = new image;
	
	//이미지가 제대로 초기화가 되지 않았다면 리턴NULL
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵*/
	//생성된 이미지를 맵안에 추가한다
	//맵 => 레드블랙트리로 만들어져 있다
	//반드시 (키, 밸류)를 쌍으로 집어넣어야 한다
	//first->키, second->밸류
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	//이미지가 존재하지 않으니까 새로 생성후 초기화
	img = new image;

	//이미지가 제대로 초기화가 되지 않았다면 리턴NULL
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵*/
	//생성된 이미지를 맵안에 추가한다
	//맵 => 레드블랙트리로 만들어져 있다
	//반드시 (키, 밸류)를 쌍으로 집어넣어야 한다
	//first->키, second->밸류
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	//이미지가 존재하지 않으니까 새로 생성후 초기화
	img = new image;

	//이미지가 제대로 초기화가 되지 않았다면 리턴NULL
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵*/
	//생성된 이미지를 맵안에 추가한다
	//맵 => 레드블랙트리로 만들어져 있다
	//반드시 (키, 밸류)를 쌍으로 집어넣어야 한다
	//first->키, second->밸류
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	//이미지가 존재하지 않으니까 새로 생성후 초기화
	img = new image;

	//이미지가 제대로 초기화가 되지 않았다면 리턴NULL
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵*/
	//생성된 이미지를 맵안에 추가한다
	//맵 => 레드블랙트리로 만들어져 있다
	//반드시 (키, 밸류)를 쌍으로 집어넣어야 한다
	//first->키, second->밸류
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	//이미지가 존재하지 않으니까 새로 생성후 초기화
	img = new image;

	//이미지가 제대로 초기화가 되지 않았다면 리턴NULL
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL 맵*/
	//생성된 이미지를 맵안에 추가한다
	//맵 => 레드블랙트리로 만들어져 있다
	//반드시 (키, 밸류)를 쌍으로 집어넣어야 한다
	//first->키, second->밸류
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::findImage(string strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면
	if (key != _mImageList.end())
	{
		return key->second;
	}

	//검색한 키로 이미지를 못찾았다면 리턴 NULL
	return NULL;
}

BOOL imageManager::deleteImage(string strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//맵의 반복자 삭제
		_mImageList.erase(key);

		return TRUE;
	}

	//검색한 키로 이미지를 못찾았다면 리턴 false;
	return FALSE;
}

BOOL imageManager::deleteAll(void)
{
	//맵 전체를 돌면서 지우자
	mapImageIter iter = _mImageList.begin();
	//for(;;) == while(true)
	for (;iter != _mImageList.end();)
	{
		//이미지가 있으니
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	//맵 전체를 삭제
	_mImageList.clear();

	return TRUE;
}
//====================================================================
//			## 일반렌더 ##
//====================================================================
void imageManager::render(string strKey, HDC hdc)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}
//====================================================================
//			## 알파렌더 ##
//====================================================================
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}


//====================================================================
//			## 프레임렌더 ##
//====================================================================
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY, alpha);
}
void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}
//====================================================================
//			## 루프렌더 ##
//====================================================================
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//이미지를 찾아서 그냥 렌더시키자
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}
