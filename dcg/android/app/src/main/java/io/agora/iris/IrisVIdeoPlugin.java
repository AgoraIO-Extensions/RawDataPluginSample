package io.agora.iris.plugin;

import android.content.Context;
import java.util.Arrays;
import java.util.List;

public class IrisPlugin {
  static { System.loadLibrary("VideoObserverPlugin"); }

  private long plugin;
  private VideoFrameObserver videoObserver;

  public IrisPlugin(long nativeHandle) {
    plugin =
        createSampePlugin(nativeHandle);
  }

  public void setObsever(VideoFrameObserver observer) {
    synchronized (this) { this.videoObserver = observer; }
  }

  public void destroy() {
    destroySampePlugin(this.plugin);
    this.plugin = 0;
  }

  public long getPlugin() { return plugin; }

  boolean enable(){
    return enablePlugin(this.plugin);
  }
  
  boolean disable(){
    return disablePlugin(this.plugin);
  }

  protected  boolean onCaptureVideoFrame(VideoFrame videoFrame){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onCaptureVideoFrame(videoFrame);
      }
    }
  }

  protected  boolean onSecondaryCameraCaptureVideoFrame(VideoFrame videoFrame){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onSecondaryCameraCaptureVideoFrame(videoFrame);
      }
    }
  }
  protected  boolean onScreenCaptureVideoFrame(VideoFrame videoFrame){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onScreenCaptureVideoFrame(videoFrame);
      }
    }
  }
  protected  boolean onSecondaryScreenCaptureVideoFrame(VideoFrame videoFrame){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onSecondaryScreenCaptureVideoFrame(videoFrame);
      }
    }
  }

  protected  boolean onMediaPlayerVideoFrame(VideoFrame videoFrame,  int mediaPlayerId){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onMediaPlayerVideoFrame(videoFrame, mediaPlayerId);
      }
    }
  }

   protected  boolean onMediaPlayerVideoFrameString channelId, int uid, VideoFrame videoFrame){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onMediaPlayerVideoFrameString(channelId, uid, videoFrame);
      }
    }
  }

    protected  boolean onTranscodedVideoFrame(VideoFrame videoFrame){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onTranscodedVideoFrame(videoFrame);
      }
    }
  }
  protected  boolean onPreEncodeVideoFrame(VideoFrame videoFrame){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onPreEncodeVideoFrame(videoFrame);
      }
    }
  }
  protected  boolean onSecondaryPreEncodeCameraVideoFrame(VideoFrame videoFrame){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onSecondaryPreEncodeCameraVideoFrame(videoFrame);
      }
    }
  }

  protected  boolean onPreEncodeScreenVideoFrame(VideoFrame videoFrame){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onPreEncodeScreenVideoFrame(videoFrame);
      }
    }
  }
    
    protected  boolean onSecondaryPreEncodeScreenVideoFrame(VideoFrame videoFrame){
    synchronized (this) {
     if (this.observer != null) {
        this.observer.onSecondaryPreEncodeScreenVideoFrame(videoFrame);
      }
    }
  }

  private native long createSampePlugin(long nativeHandle);

  private native void destroySampePlugin(long plugin);

  private native boolean enablePlugin(long plugin);

  private native boolean disablePlugin(long plugin);
}
