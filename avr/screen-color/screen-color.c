#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CGDirectDisplay.h>
#include <CoreGraphics/CGDisplayConfiguration.h>
#include <CoreGraphics/CGDisplayFade.h>
#include <CoreGraphics/CGDisplayStream.h>
#include <CoreGraphics/CGRemoteOperation.h>
#include <CoreGraphics/CGSession.h>
#include <CoreGraphics/CGWindowLevel.h>
#include <CoreGraphics/CGImage.h>


void captureScreen(){
    CGImageRef image_ref = CGDisplayCreateImage(CGMainDisplayID()); 
    CFDataRef rawData = CGDataProviderCopyData(CGImageGetDataProvider(image_ref));
    UInt8 *buf = (UInt8 *) CFDataGetBytePtr(rawData); 
    int size = CFDataGetLength(rawData);

    int redAverage = 0;
    int greenAverage = 0;
    int blueAverage = 0;

    for (int i = 0; i + 3 < size; i+=4) {
        blueAverage += buf[i];
        greenAverage += buf[i + 1];
        redAverage += buf[i + 2]; 
    }
    CFRelease(rawData);    
    CGImageRelease(image_ref); 

    redAverage /= size / 4;
    greenAverage /= size / 4;
    blueAverage /= size / 4;

    if (redAverage < 125)
        redAverage = 0;
    else
        redAverage = 1;

    if (greenAverage < 125)
        greenAverage = 0;
    else 
        greenAverage = 1;

    if (blueAverage < 125)
        blueAverage = 0;
    else
        blueAverage = 1;

   printf("%d %d %d", size, greenAverage, blueAverage);
}

int main() {
    captureScreen();
    return 0;
}
