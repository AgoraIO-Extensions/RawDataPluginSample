package io.agora.iris;

import java.util.List;

public interface IrisEventHandler {
  void OnEvent(String event, String data, List<byte[]> buffers);
}
