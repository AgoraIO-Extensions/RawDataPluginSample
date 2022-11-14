import 'package:flutter_test/flutter_test.dart';
import 'package:video_raw_data/video_raw_data.dart';
import 'package:video_raw_data/video_raw_data_platform_interface.dart';
import 'package:video_raw_data/video_raw_data_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockVideoRawDataPlatform 
    with MockPlatformInterfaceMixin
    implements VideoRawDataPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final VideoRawDataPlatform initialPlatform = VideoRawDataPlatform.instance;

  test('$MethodChannelVideoRawData is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelVideoRawData>());
  });

  test('getPlatformVersion', () async {
    VideoRawData videoRawDataPlugin = VideoRawData();
    MockVideoRawDataPlatform fakePlatform = MockVideoRawDataPlatform();
    VideoRawDataPlatform.instance = fakePlatform;
  
    expect(await videoRawDataPlugin.getPlatformVersion(), '42');
  });
}
