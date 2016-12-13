#include <string.h>
#include <stdlib.h>
#include <android/log.h>

#include "zbar.h"
#include "image.h"
#include "com_th_zbar_build_ZBarDecoder.h"

#define   WIDTHBYTES(bits)         (((bits)   +   31)   /   32   *   4)
static zbar_image_scanner_t *scanner = NULL;

JNIEXPORT jstring JNICALL Java_com_th_zbar_build_ZBarDecoder_decodeRaw(
		JNIEnv *env, jobject obj, jbyteArray img, jint width, jint height) {

	zbar_image_scanner_t *scanner;
	zbar_image_t *zimage;
	zbar_image_t *zgrayimage;

	jbyte *pixbuf;
	jstring s = NULL;

	zbar_set_verbosity(10); // XXX

	pixbuf = (*env)->GetByteArrayElements(env, img, 0);

	zimage = zbar_image_create();
	if (zimage == NULL) {
		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
		return NULL;
	}

	zbar_image_set_format(zimage, *(unsigned long *) "Y800");
	zbar_image_set_size(zimage, width, height);
	zbar_image_set_data(zimage, pixbuf, (*env)->GetArrayLength(env, img),
			zbar_image_free_data);

	zgrayimage = zbar_image_convert(zimage, *(unsigned long *) "Y800");
	if (zgrayimage == NULL) {
		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
		return NULL;
	}

	zbar_image_destroy(zimage);

	scanner = zbar_image_scanner_create();
	zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);
	zbar_scan_image(scanner, zgrayimage);

	const zbar_symbol_t *sym;

	sym = zbar_image_first_symbol(zgrayimage);
	if (sym != NULL) {
		const char *sym_data;
		sym_data = zbar_symbol_get_data(sym);
		__android_log_print(ANDROID_LOG_DEBUG, "zbar", "url: %s", sym_data);
		s = (*env)->NewStringUTF(env, sym_data);
	}

	(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
	return s;
}


JNIEXPORT void JNICALL Java_com_th_zbar_build_ZBarDecoder_create(JNIEnv *env, jobject obj)
{
	if(scanner == NULL)
			scanner = zbar_image_scanner_create();
}


JNIEXPORT void JNICALL Java_com_th_zbar_build_ZBarDecoder_destroy(JNIEnv *env, jobject obj)
{
	if (scanner != NULL)
	{
		zbar_image_scanner_destroy(scanner);
		scanner = NULL;
	}
}

JNIEXPORT jstring JNICALL Java_com_th_zbar_build_ZBarDecoder_decodeCrop(
		JNIEnv *env, jobject obj, jbyteArray img, jint width, jint height,
		jint x, jint y, jint cropw, jint croph) {


//	zbar_image_t *zimage;
//	zbar_image_t *zgrayimage;
//
//	jbyte *pixbuf;
//	jstring s = NULL;
//
//	zbar_set_verbosity(10); // XXX
//
//	pixbuf = (*env)->GetByteArrayElements(env, img, 0);
//
//	zimage = zbar_image_create();
//	if (zimage == NULL) {
//		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
//		return NULL;
//	}
//
//	zbar_image_set_format(zimage, *(unsigned long *) "Y800");
//	zbar_image_set_size(zimage, width, height);
//	zbar_image_set_data(zimage, pixbuf, (*env)->GetArrayLength(env, img),
//			zbar_image_free_data);
//
//	zbar_image_set_crop(zimage, x, y, cropw, croph);
//
//	zgrayimage = zbar_image_convert(zimage, *(unsigned long *) "Y800");
//	if (zgrayimage == NULL) {
//		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
//		return NULL;
//	}
//
//	if (zimage != NULL) {
//		zbar_image_destroy(zimage);
//		zimage = NULL;
//	}
//
//	if(scanner == NULL)
//		scanner = zbar_image_scanner_create();
//	zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);
//	zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_X_DENSITY, 3);
//	zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_Y_DENSITY, 3);
//	zbar_scan_image(scanner, zgrayimage);
//
//	const zbar_symbol_t *sym;
//
//	sym = zbar_image_first_symbol(zgrayimage);
//	if (sym != NULL) {
//		const char *sym_data;
//		sym_data = zbar_symbol_get_data(sym);
//		__android_log_print(ANDROID_LOG_DEBUG, "zbar", "url: %s", sym_data);
//		s = (*env)->NewStringUTF(env, sym_data);
//	}
//
////	while (sym) {
////			const char *sym_data;
////			sym_data = zbar_symbol_get_data(sym);
////			__android_log_print(ANDROID_LOG_DEBUG, "zbar", "url: %s", sym_data);
////
////			sym = zbar_symbol_next(sym);
////			if (sym == NULL) {
////				s = (*env)->NewStringUTF(env, sym_data);
////			}
////		}
//
//		done:
//	//	if(pixbufOut != NULL)
//	//	{
//	//		free(pixbufOut);
//	//		pixbufOut = NULL;
//	//
//	//	}
//
////		if (scanner != NULL) {
////			zbar_image_scanner_destroy(scanner);
////			scanner = NULL;
////		}
//
//
//
//
//	(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
//	return s;
	zbar_image_scanner_t *scanner;
		zbar_image_t *zimage;
		zbar_image_t *zgrayimage;

		jbyte *pixbuf;
		jstring s = NULL;

		zbar_set_verbosity(10); // XXX

		pixbuf = (*env)->GetByteArrayElements(env, img, 0);

		zimage = zbar_image_create();
		if (zimage == NULL) {
			(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
			return NULL;
		}

		zbar_image_set_format(zimage, *(unsigned long *) "Y800");
		zbar_image_set_size(zimage, width, height);
		zbar_image_set_data(zimage, pixbuf, (*env)->GetArrayLength(env, img),
				zbar_image_free_data);

		zbar_image_set_crop(zimage, x, y, cropw, croph);

		zgrayimage = zbar_image_convert(zimage, *(unsigned long *) "Y800");
		if (zgrayimage == NULL) {
			(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
			return NULL;
		}

		zbar_image_destroy(zimage);

		scanner = zbar_image_scanner_create();
		zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);
		zbar_scan_image(scanner, zgrayimage);

		const zbar_symbol_t *sym;

		sym = zbar_image_first_symbol(zgrayimage);
		if (sym != NULL) {
			const char *sym_data;
			sym_data = zbar_symbol_get_data(sym);
			__android_log_print(ANDROID_LOG_DEBUG, "zbar", "url: %s", sym_data);
			s = (*env)->NewStringUTF(env, sym_data);
		}

		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
		return s;
}

static unsigned char * ConvertToBrightHigher(unsigned char *in, int width,
		int height) {

	unsigned char *out = NULL;
	long lLineBytes = WIDTHBYTES(width * 8); // 计算图像每行的字节数
	int i = 0, j = 0;
	// 每行
	for (i = 0; i < height; i++) {
		// 每列
		for (j = 0; j < width; j++) {
			// 指向DIB第i行，第j个象素的指针
			out = (unsigned char*) in + lLineBytes * (height - 1 - i) + j;

			// 计算新的灰度值
			if (*out < 239)
				*(out) = (unsigned char) (16 + *out);
		}
	}

	return out;
}

static unsigned char * ConvertToBrightLower(unsigned char *in, int width,
		int height) {

	unsigned char *out = NULL;
	long lLineBytes = WIDTHBYTES(width * 8); // 计算图像每行的字节数
	int i = 0, j = 0;
	// 每行
	for (i = 0; i < height; i++) {
		// 每列
		for (j = 0; j < width; j++) {
			// 指向DIB第i行，第j个象素的指针
			out = (unsigned char*) in + lLineBytes * (height - 1 - i) + j;

			// 计算新的灰度值
			if (*out < 239)
				*(out) = (unsigned char) (*out - 16);
		}
	}

	return out;
}

static void ConvertToSharp(unsigned char *in, int width, int height) {

	long DibWidth = WIDTHBYTES(width * 8); // 计算图像每行的字节数

	int j = 0;
	int i = 0;
	int pby_pt = 0;
	int value = 0;
	unsigned char *p_temp1 = NULL, *p_temp2 = NULL;
	unsigned char *p_temp = (unsigned char *) malloc(
			sizeof(unsigned char) * height * DibWidth);

	for (j = 0; j < height - 1; j++) // 每行
	{
		for (i = 0; i < DibWidth - 5; i++) // 每列
		{
			pby_pt = 0;
			pby_pt = *(in + (height - j - 2) * DibWidth + i + 3)
					- *(in + (height - j - 1) * DibWidth + i);
			p_temp1 = p_temp+((height-j-2)*DibWidth+i+3);
			p_temp2 = in+((height-j-2)*DibWidth+i+3);
			value = (int)(pby_pt/4);
			if(value < 0){
				value = -value;
			}

			*(p_temp1) = *(p_temp2) + value;



			if (*(p_temp + (height - j - 2) * DibWidth + i + 3) > 255)
				*(p_temp + (height - j - 2) * DibWidth + i + 3) = 255;
		}
	}

	memcpy(in, p_temp, height * DibWidth); // 复制处理后的图像

	free(p_temp);

	p_temp = NULL;
}

static unsigned char * ConvertGRAY(unsigned char *in, int width, int height)
{
	long lLineBytes = WIDTHBYTES(width * 8);     // 计算图像每行的字节数
	int i = 0, j = 0;
	const float c1=150,c2=2.5;
	unsigned char *lpSrc;

		// 每行
	for(i = 0; i < height; i++)
	{
		// 每列
		for(j = 0; j < width; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)in + lLineBytes * (height - 1 - i) + j;

			// 计算新的灰度值
			if(*lpSrc<122)
				*lpSrc=(unsigned char)0;
			else
				*lpSrc = (unsigned char)(255);
		}
	}

}

static void ConvertRGBToGRAY(unsigned char *in, unsigned char *out, int width,
		int height) {
	int sz = width * height;
	int type = 1;
	int i = 0;

	for (i = 0; i < sz; i++) {
		out[i] = (jbyte)(
				(((in[i] & 0x00ff0000) >> 16) * 19595
						+ ((in[i] & 0x0000ff00) >> 8) * 38469
						+ ((in[i] & 0x000000ff)) * 7472) >> 16);
	}

//	if (type == 0) //RGBA
//	{
//		for(i=0;i<sz;i++)
//		{
//			float A,R,G,B;
//			R=in[i*4+0];
//			G=in[i*4+1];
//			B=in[i*4+2];
//			//A=arr[i*4+3];
//			unsigned char ir = 0.2989 * R + 0.5870 * G + 0.1140 * B;
//			out[i] = ir;
//		}
//	}
//	else if(type == 1) //RGB565
//	{
//		uint16_t *parr = (uint16_t*)in;
//		for(i=0;i<sz;i++)
//		{
//			float A,R,G,B;
//			R = ((parr[i] & 0xF800)>> 11) *8;
//			G = ((parr[i] & 0x07e0)>> 5) *4;
//			B = ((parr[i] & 0x001F)>> 0) *8;
//			unsigned char ir = 0.2989 * R + 0.5870 * G + 0.1140 * B;
//			out[i] = ir;
//		}
//	}
}

JNIEXPORT jstring JNICALL Java_com_th_zbar_build_ZBarDecoder_decodeCrop2(
		JNIEnv *env, jobject obj, jbyteArray img, jint width, jint height,
		jint x, jint y, jint cropw, jint croph) {

	zbar_image_scanner_t *scanner;
	zbar_image_t *zimage;
	zbar_image_t *zgrayimage;

	jbyte *pixbuf;
	jstring s = NULL;

	zbar_set_verbosity(10); // XXX
//	unsigned char *pixbufOut = NULL;
	pixbuf = (*env)->GetByteArrayElements(env, img, 0);
//	char *pixbufOut = (char*)malloc(sizeof(char) * width*height);
//	if(pixbufOut == NULL){
//		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
//		return NULL;
//	}

//	ConvertRGBToGRAY(pixbuf, pixbufOut, width, height);
//	pixbufOut = ConvertToBrightHigher(pixbuf, width, height);

//	ConvertToSharp(pixbuf, width, height);
//	ConvertGRAY(pixbuf, width, height);
	zimage = zbar_image_create();
	if (zimage == NULL) {
		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
//		free(pixbufOut);
//		pixbufOut = NULL;
		return NULL;
	}

	zbar_image_set_format(zimage, *(unsigned long *) "Y800");
	zbar_image_set_size(zimage, width, height);
	zbar_image_set_data(zimage, pixbuf, (*env)->GetArrayLength(env, img),
			zbar_image_free_data);

	zbar_image_set_crop(zimage, x, y, cropw, croph);

	zgrayimage = zbar_image_convert(zimage, *(unsigned long *) "Y800");
	if (zgrayimage == NULL) {
		(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
//		free(pixbufOut);
//		pixbufOut = NULL;
		return NULL;
	}

	scanner = zbar_image_scanner_create();
	if (scanner == NULL)
		goto done;

	zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);
//	zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_X_DENSITY, 3);
//	zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_Y_DENSITY, 3);
	zbar_image_scanner_recycle_image(scanner, zimage);
	zbar_scan_image(scanner, zgrayimage);
	_zbar_image_swap_symbols(zimage, zgrayimage);
//	if(zgrayimage != NULL){
//			zbar_image_destroy(zgrayimage);
//			zgrayimage = NULL;
//	}

	const zbar_symbol_t *sym;

	sym = zbar_image_first_symbol(zimage);

	while (sym) {
		const char *sym_data;
		sym_data = zbar_symbol_get_data(sym);
		__android_log_print(ANDROID_LOG_DEBUG, "zbar", "url: %s", sym_data);

		sym = zbar_symbol_next(sym);
		if (sym == NULL) {
			s = (*env)->NewStringUTF(env, sym_data);
		}
	}

	done:
//	if(pixbufOut != NULL)
//	{
//		free(pixbufOut);
//		pixbufOut = NULL;
//
//	}

	if (scanner != NULL) {
		zbar_image_scanner_destroy(scanner);
		scanner = NULL;
	}

	if (zimage != NULL) {
		zbar_image_destroy(zimage);
		zimage = NULL;
	}

	(*env)->ReleaseByteArrayElements(env, img, pixbuf, 0);
	return s;
}
