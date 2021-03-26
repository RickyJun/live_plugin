import 'dart:math';

class Utils {
  static String getRandomAlphaString(int length, {String base}) {
    base ??= "abcdefghijklmnopqrstuvwxyz";
    Random random = new Random();
    String res = "";
    for (int i = 0; i < length; i++) {
      int number = random.nextInt(base.length);
      res = res + (base[number]);
    }
    return res;
  }

  static String getRandomAlphaDigitString(int length) =>
      getRandomAlphaString(length,
          base: "abcdefghijklmnopqrstuvwxyz0123456789");
}
