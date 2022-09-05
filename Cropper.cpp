#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ostream>

int main()
{
	const unsigned int CROPWIDTH = 40;
	const unsigned int CROPHEIGHT = 492;
	const int BITSPERPIXEL = 24;
	const int BYTESPERPIXEL = 3;
		
	//Magic numbers correspond to original names and amount of pictures
    for(int bmap = 6; bmap < 128; bmap++)
    {
        char ifilename[32];
        char ofilename[32];
        
        sprintf(ifilename, "PSOGL2_%03d.bmp", bmap);
        sprintf(ofilename, "Cropped_%d.bmp", bmap);

        std::ifstream input(ifilename, std::ios::binary);
        std::ofstream output;
        output.open(ofilename, std::ios::out | std::ios::binary);



        char header[14];
        char InfoHeader[40];
        char buffer[CROPWIDTH * BYTESPERPIXEL];
        char data[CROPHEIGHT * CROPWIDTH * BYTESPERPIXEL];

        if(input.is_open()){}
        else{std::cout << "Could not open input \n";}

        input.read(header, 14);
        input.read(InfoHeader, 40);

        int Bottom = 54 + (1350 * BYTESPERPIXEL) + (((900 - 560) * BYTESPERPIXEL) * 1440);
        input.seekg(Bottom, std::ios::beg);


        long long int counter = 0;

        for(int i = 0; i < CROPHEIGHT; i++)
        {
            input.read(buffer, CROPWIDTH * BYTESPERPIXEL);

            for(int j = 0; j < CROPWIDTH; j++)
            {
                for(int k = 0; k < BYTESPERPIXEL; k++)
                {
                    data[counter] = buffer[j * BYTESPERPIXEL + k];
                    counter++;
                }
                
            }

            input.seekg((Bottom + i * 1440 * BYTESPERPIXEL), std::ios::beg);
        }

        unsigned int croppedsize;
        croppedsize = CROPHEIGHT * CROPWIDTH * BYTESPERPIXEL + 14 + 40;

        header[2] = croppedsize & 0xff;
        header[3] = (croppedsize>>8) & 0xff;
        header[4] = (croppedsize>>16) & 0xff;
        header[5] = (croppedsize>>24) & 0xff;

        InfoHeader[4] = CROPWIDTH & 0xff;
        InfoHeader[5] = (CROPWIDTH>>8) & 0xff;
        InfoHeader[6] = (CROPWIDTH>>16) & 0xff;
        InfoHeader[7] = (CROPWIDTH>>24) & 0xff;


        InfoHeader[8] = CROPHEIGHT & 0xff;
        InfoHeader[9] = (CROPHEIGHT>>8) & 0xff;
        InfoHeader[10] = (CROPHEIGHT>>16) & 0xff;
        InfoHeader[11] = (CROPHEIGHT>>24) & 0xff;
        

        if(output.is_open())
        {
            output.write(header, 14);
            output.write(InfoHeader, 40);
            output.write(data, CROPHEIGHT * CROPWIDTH * BYTESPERPIXEL);
        }
        else{std::cout << "Could not open output \n";}

        input.close();
        output.close();   

    }

    return 0;
}