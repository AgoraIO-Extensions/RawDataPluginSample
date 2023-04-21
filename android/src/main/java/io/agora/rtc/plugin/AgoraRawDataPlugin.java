package io.agora.rtc.plugin;

public class AgoraRawDataPlugin {
  static { System.loadLibrary("AgoraRawDataPlugin"); }

  private long handle;
  private long handleAudio;

  public AgoraRawDataPlugin(long nativeHandle) {
    handle = createSamplePlugin(nativeHandle);
    handleAudio = createSampleAudioPlugin(nativeHandle);
  }

  public void destroy() {
    destroySamplePlugin(this.handle);
    this.handle = 0;
    destroySamplePlugin(this.handleAudio);
    this.handleAudio = 0;
  }

  public boolean enablePlugin() { return enablePlugin(this.handle); }

  public boolean disablePlugin() { return disablePlugin(this.handle); }

  public boolean enableAudioPlugin() { return enablePlugin(this.handleAudio); }

  public boolean disableAudioPlugin() {
    return disablePlugin(this.handleAudio);
  }

  private native long createSamplePlugin(long nativeHandle);

  private native void destroySamplePlugin(long handle);

  private native long createSampleAudioPlugin(long nativeHandle);

  private native boolean enablePlugin(long handle);

  private native boolean disablePlugin(long handle);
}
