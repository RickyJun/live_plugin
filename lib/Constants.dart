class Bitrates {
  final String value;
  final int intValue;
  const Bitrates(this.value, this.intValue);
  static const Bitrates Bitrate352x288 = Bitrates("352x288", 352 * 288);
  static const Bitrates Bitrate960x540 = Bitrates("960x540", 960 * 540);
}

class Filters {
  final String value;
  const Filters(this.value);
  static const Filters GPUImageBeautyFilter = Filters("GPUImageBeautyFilter");
}
