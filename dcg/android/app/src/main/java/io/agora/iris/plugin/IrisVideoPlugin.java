package io.agora.iris.plugin;

public class IrisVideoPlugin {
  static { System.loadLibrary("VideoObserverPlugin"); }

  private long handle;

  public IrisVideoPlugin(long nativeHandle) {
    handle = createSamplePlugin(nativeHandle);
  }

  public void destroy() {
    destroySamplePlugin(this.handle);
    this.handle = 0;
  }

  boolean enable() { return enablePlugin(this.handle); }

  boolean disable() { return disablePlugin(this.handle); }

  private native long createSamplePlugin(long nativeHandle);

  private native void destroySamplePlugin(long handle);

  private native boolean enablePlugin(long handle);

  private native boolean disablePlugin(long handle);
}
