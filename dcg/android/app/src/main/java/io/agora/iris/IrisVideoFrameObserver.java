import package io.agora.base;

public interface VideoFrameObserver {
  boolean OnCaptureVideoFrame(VideoFrame videoFrame);

  boolean onSecondaryCameraCaptureVideoFrame(VideoFrame videoFrame);

  boolean onScreenCaptureVideoFrame(VideoFrame videoFrame);

  boolean onSecondaryScreenCaptureVideoFrame(VideoFrame videoFrame);

  boolean onMediaPlayerVideoFrame(VideoFrame videoFrame, int mediaPlayerId);

  boolean onRenderVideoFrame(String channelId, int uid, VideoFrame videoFrame);

  boolean onTranscodedVideoFrame(VideoFrame videoFrame);

  boolean onPreEncodeVideoFrame(VideoFrame videoFrame);

  boolean onSecondaryPreEncodeCameraVideoFrame(VideoFrame videoFrame);

  boolean onPreEncodeScreenVideoFrame(VideoFrame videoFrame);

  boolean onSecondaryPreEncodeScreenVideoFrame(VideoFrame videoFrame);
}
