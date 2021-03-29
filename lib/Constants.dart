class Bitrates {
  final String value;
  const Bitrates(this.value);
  static const Bitrates Bitrate352x288 = Bitrates("352x288");
  static const Bitrates Bitrate960x540 = Bitrates("960x540");
}

class Filters {
  final String value;
  const Filters(this.value);
  static const Filters GPUImageBeautyFilter = Filters("GPUImageBeautyFilter");
}
