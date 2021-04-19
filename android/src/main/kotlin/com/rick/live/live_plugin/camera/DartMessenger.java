// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package com.rick.live.live_plugin.camera;

import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;

import androidx.annotation.Nullable;

import com.rick.live.live_plugin.camera.types.ExposureMode;
import com.rick.live.live_plugin.camera.types.FocusMode;

import java.util.HashMap;
import java.util.Map;

import io.flutter.embedding.engine.systemchannels.PlatformChannel;
import io.flutter.plugin.common.BinaryMessenger;
import io.flutter.plugin.common.MethodChannel;


public class DartMessenger {
  @Nullable private MethodChannel cameraChannel;
  @Nullable private MethodChannel deviceChannel;

  enum DeviceEventType {
    ORIENTATION_CHANGED("orientation_changed");
    private final String method;

    DeviceEventType(String method) {
      this.method = method;
    }
  }

  enum CameraEventType {
    ERROR("error"),
    CLOSING("camera_closing"),
    INITIALIZED("initialized");

    private final String method;

    CameraEventType(String method) {
      this.method = method;
    }
  }

  public DartMessenger(BinaryMessenger messenger, long cameraId) {
    cameraChannel = new MethodChannel(messenger, "flutter.io/cameraPlugin/camera" + cameraId);
    deviceChannel = new MethodChannel(messenger, "flutter.io/cameraPlugin/device");
  }

  void sendDeviceOrientationChangeEvent(final PlatformChannel.DeviceOrientation orientation) {
    assert (orientation != null);
    this.send(
        DeviceEventType.ORIENTATION_CHANGED,
        new HashMap<String, Object>() {
          {
            put("orientation", CameraUtils.serializeDeviceOrientation(orientation));
          }
        });
  }

  void sendCameraInitializedEvent(
          final Integer previewWidth,
          final Integer previewHeight,
          final ExposureMode exposureMode,
          final FocusMode focusMode,
          final Boolean exposurePointSupported,
          final Boolean focusPointSupported) {
    assert (previewWidth != null);
    assert (previewHeight != null);
    assert (exposureMode != null);
    assert (focusMode != null);
    assert (exposurePointSupported != null);
    assert (focusPointSupported != null);
    this.send(
        CameraEventType.INITIALIZED,
        new HashMap<String, Object>() {
          {
            put("previewWidth", previewWidth.doubleValue());
            put("previewHeight", previewHeight.doubleValue());
            put("exposureMode", exposureMode.toString());
            put("focusMode", focusMode.toString());
            put("exposurePointSupported", exposurePointSupported);
            put("focusPointSupported", focusPointSupported);
          }
        });
  }

  void sendCameraClosingEvent() {
    send(CameraEventType.CLOSING);
  }

  void sendCameraErrorEvent(@Nullable final String description) {
    this.send(
        CameraEventType.ERROR,
        new HashMap<String, Object>() {
          {
            if (!TextUtils.isEmpty(description)) put("description", description);
          }
        });
  }

  void send(final CameraEventType eventType) {
    this.send(eventType, new HashMap<String,Object>());
  }

  void send(final CameraEventType eventType, final Map<String, Object> args) {
    if (cameraChannel == null) {
      return;
    }
    new Handler(Looper.getMainLooper())
        .post(
            new Runnable() {
              @Override
              public void run() {
                cameraChannel.invokeMethod(eventType.method, args);
              }
            });
  }

  void send(final DeviceEventType eventType) {
    send(eventType, new HashMap<String,Object>());
  }

  void send(final DeviceEventType eventType, final Map<String, Object> args) {
    if (deviceChannel == null) {
      return;
    }
    new Handler(Looper.getMainLooper())
        .post(
            new Runnable() {
              @Override
              public void run() {
                deviceChannel.invokeMethod(eventType.method, args);
              }
            });
  }
}
