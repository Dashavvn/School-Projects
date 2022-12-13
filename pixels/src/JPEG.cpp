#include "JPEG.h"

void writeJpeg(const char* filename,Image* image, int quality){
	struct jpeg_compress_struct info;

    FILE* outFile = fopen(filename,"wb");
    if(outFile == NULL){
        return;
    }

	if(image->channels > 3){
		image->removeAlpha();
	}

    struct jpeg_error_mgr pub;
    info.err = jpeg_std_error(&pub);

	jpeg_create_compress(&info);
	jpeg_stdio_dest(&info,outFile);

	info.image_width = image->width;
    info.image_height = image->height;
    info.input_components = 3;
	info.in_color_space = JCS_RGB;

	jpeg_set_defaults(&info);
	jpeg_set_quality(&info,quality,TRUE);
	
	jpeg_start_compress(&info,TRUE);
	
	unsigned char* buffer;
	int rowStride = image->width*3;
	while(info.next_scanline < image->height){
	    buffer = image->data+info.next_scanline * rowStride;
        jpeg_write_scanlines(&info, &buffer, 1);
	}
	
	jpeg_finish_compress(&info);
	fclose(outFile);
	jpeg_destroy_compress(&info);

}


Image* readJpeg(const char* filename){
	struct jpeg_decompress_struct info;

	FILE* inFile = fopen(filename,"rb");
	if(inFile == NULL){
		return 0;
	}

	struct jpeg_error_mgr pub;
	info.err = jpeg_std_error(&pub);

	jpeg_create_decompress(&info);
	jpeg_stdio_src(&info, inFile);

	jpeg_read_header(&info, TRUE);

	jpeg_start_decompress(&info);
	
	Image* image = new Image(info.output_width,info.output_height,info.num_components);

	unsigned char* buffer;

	int rowStride = image->width*image->channels;
	while (info.output_scanline < image->height){
		buffer = image->data+info.output_scanline * rowStride;
		jpeg_read_scanlines(&info, &buffer, 1);
	}

	jpeg_finish_decompress(&info);
	jpeg_destroy_decompress(&info);
	fclose(inFile);       

	return image;
}





