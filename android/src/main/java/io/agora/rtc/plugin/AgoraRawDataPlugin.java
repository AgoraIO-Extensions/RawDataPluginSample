package io.agora.rtc.plugin;

public class AgoraRawDataPlugin {
  static { System.loadLibrary("AgoraRawDataPlugin"); }

  private long handle;

  public AgoraRawDataPlugin(long nativeHandle) {
    handle = createSamplePlugin(nativeHandle);
  }

  public void destroy() {
    destroySamplePlugin(this.handle);
    this.handle = 0;
  }

  public boolean enablePlugin() { return enablePlugin(this.handle); }

  public boolean disablePlugin() { return disablePlugin(this.handle); }

  private native long createSamplePlugin(long nativeHandle);

  private native void destroySamplePlugin(long handle);

  private native boolean enablePlugin(long handle);

  private native boolean disablePlugin(long handle);
}
