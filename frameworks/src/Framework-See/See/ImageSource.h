//
//  ImageSource.h
//  Framework-See
//
//	Created by Marynel Vazquez on 11/18/10.
//	Copyright 2010 Carnegie Mellon University
//
//	This work was developed under the Rehabilitation Engineering Research 
//	Center on Accessible Public Transportation (www.rercapt.org) and is funded 
//	by grant number H133E080019 from the United States Department of Education 
//	through the National Institute on Disability and Rehabilitation Research. 
//	No endorsement should be assumed by NIDRR or the United States Government 
//	for the content contained on this code.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import <AVFoundation/AVFoundation.h>

/*! Image source delegate protocol */
@protocol ImageSourceDelegate <NSObject>
@optional
- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withPresentationTime:(CMTime)time;
@end

/*! Image sources manager
 */
@interface ImageSource : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate> {
	AVCaptureDeviceInput *cameraInput;				//!< camera input
    AVCaptureVideoDataOutput *cameraOutput;         //!< video data output
//    AVCaptureStillImageOutput *stillCameraOutput;   //!< still image camera output
    
	AVAssetWriter *writer;							//!< video writer
	AVAssetWriterInput *writerInput;				//!< video writer input
	NSURL *videoPath;                               //!< video path
	CMTime recordTime;                              //!< record time
	BOOL record;                                    //!< record?
    dispatch_queue_t frameGrabberQueue;             //!< serial queue to save video frames
}

@property (nonatomic, assign) id <ImageSourceDelegate> delegate;
@property (nonatomic, retain) AVCaptureSession *session;
@property (nonatomic, strong) dispatch_queue_t frameGrabberQueue;           

- (id) init;
- (BOOL) setupCaptureSessionWithPreset:(NSString *)preset error:(NSError **)error;
- (BOOL) setupCaptureSessionWithPreset:(NSString *)preset videoOrientation:(AVCaptureVideoOrientation)videoOrientation error:(NSError **)error;
- (BOOL) startCaptureSession;
- (BOOL) stopCapturingSession;
- (AVCaptureVideoPreviewLayer*) layerWithSession;
- (BOOL) setupVideoWriter:(NSURL *)url width:(int)width height:(int)height error:(NSError **)error;
- (BOOL) isWriting;
- (BOOL) saveCurrentFrame:(CMSampleBufferRef)frameSampleBuffer path:(NSString*)framePath;
- (BOOL) autofocus;
//- (BOOL) saveCurrentFrameWithHandler:(void (^)(CMSampleBufferRef imageDataSampleBuffer, NSError *error))handler;
@end
