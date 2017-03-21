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
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	//�̹����� �������� �����ϱ� ���� ������ �ʱ�ȭ
	img = new image;
	
	//�̹����� ����� �ʱ�ȭ�� ���� �ʾҴٸ� ����NULL
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ��*/
	//������ �̹����� �ʾȿ� �߰��Ѵ�
	//�� => �����Ʈ���� ������� �ִ�
	//�ݵ�� (Ű, ���)�� ������ ����־�� �Ѵ�
	//first->Ű, second->���
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	//�̹����� �������� �����ϱ� ���� ������ �ʱ�ȭ
	img = new image;

	//�̹����� ����� �ʱ�ȭ�� ���� �ʾҴٸ� ����NULL
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ��*/
	//������ �̹����� �ʾȿ� �߰��Ѵ�
	//�� => �����Ʈ���� ������� �ִ�
	//�ݵ�� (Ű, ���)�� ������ ����־�� �Ѵ�
	//first->Ű, second->���
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	//�̹����� �������� �����ϱ� ���� ������ �ʱ�ȭ
	img = new image;

	//�̹����� ����� �ʱ�ȭ�� ���� �ʾҴٸ� ����NULL
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ��*/
	//������ �̹����� �ʾȿ� �߰��Ѵ�
	//�� => �����Ʈ���� ������� �ִ�
	//�ݵ�� (Ű, ���)�� ������ ����־�� �Ѵ�
	//first->Ű, second->���
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	//�̹����� �������� �����ϱ� ���� ������ �ʱ�ȭ
	img = new image;

	//�̹����� ����� �ʱ�ȭ�� ���� �ʾҴٸ� ����NULL
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ��*/
	//������ �̹����� �ʾȿ� �߰��Ѵ�
	//�� => �����Ʈ���� ������� �ִ�
	//�ݵ�� (Ű, ���)�� ������ ����־�� �Ѵ�
	//first->Ű, second->���
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	//�̹����� �������� �����ϱ� ���� ������ �ʱ�ȭ
	img = new image;

	//�̹����� ����� �ʱ�ȭ�� ���� �ʾҴٸ� ����NULL
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/*STL ��*/
	//������ �̹����� �ʾȿ� �߰��Ѵ�
	//�� => �����Ʈ���� ������� �ִ�
	//�ݵ�� (Ű, ���)�� ������ ����־�� �Ѵ�
	//first->Ű, second->���
	//_mImageList.insert(pair<string, image*>(strKey, img));
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::findImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != _mImageList.end())
	{
		return key->second;
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� ���� NULL
	return NULL;
}

BOOL imageManager::deleteImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != _mImageList.end())
	{
		//�̹��� ����
		key->second->release();
		//�޸� ����
		SAFE_DELETE(key->second);
		//���� �ݺ��� ����
		_mImageList.erase(key);

		return TRUE;
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� ���� false;
	return FALSE;
}

BOOL imageManager::deleteAll(void)
{
	//�� ��ü�� ���鼭 ������
	mapImageIter iter = _mImageList.begin();
	//for(;;) == while(true)
	for (;iter != _mImageList.end();)
	{
		//�̹����� ������
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

	//�� ��ü�� ����
	_mImageList.clear();

	return TRUE;
}
//====================================================================
//			## �Ϲݷ��� ##
//====================================================================
void imageManager::render(string strKey, HDC hdc)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}
//====================================================================
//			## ���ķ��� ##
//====================================================================
void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}


//====================================================================
//			## �����ӷ��� ##
//====================================================================
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY, alpha);
}
void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}
//====================================================================
//			## �������� ##
//====================================================================
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//�̹����� ã�Ƽ� �׳� ������Ű��
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}
