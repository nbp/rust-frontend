/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "MediaControlKeysEvent.h"

#include "MediaControlUtils.h"
#include "MediaControlService.h"
#include "mozilla/Logging.h"

extern mozilla::LazyLogModule gMediaControlLog;

namespace mozilla {
namespace dom {

static const char* ToMediaControlKeysEventStr(MediaControlKeysEvent aKeyEvent) {
  switch (aKeyEvent) {
    case MediaControlKeysEvent::ePlayPause:
      return "PlayPause";
    case MediaControlKeysEvent::eNext:
      return "Next";
    case MediaControlKeysEvent::ePrev:
      return "Prev";
    default:
      MOZ_ASSERT_UNREACHABLE("Invalid action.");
  }
  return "Unknown";
}

// avoid redefined macro in unified build
#undef LOG_SOURCE
#define LOG_SOURCE(msg, ...)                 \
  MOZ_LOG(gMediaControlLog, LogLevel::Debug, \
          ("MediaControlKeysEventSource=%p, " msg, this, ##__VA_ARGS__))

#undef LOG_KEY
#define LOG_KEY(msg, key, ...)                                    \
  if (MOZ_LOG_TEST(gMediaControlLog, mozilla::LogLevel::Debug)) { \
    MOZ_LOG(gMediaControlLog, LogLevel::Debug,                    \
            ("MediaControlKeysHandler=%p, " msg, this,            \
             ToMediaControlKeysEventStr(key), ##__VA_ARGS__));    \
  }

NS_IMPL_ISUPPORTS0(MediaControlKeysHandler)

void MediaControlKeysHandler::OnKeyPressed(MediaControlKeysEvent aKeyEvent) {
  LOG_KEY("OnKeyPressed '%s'", aKeyEvent);
  switch (aKeyEvent) {
    case MediaControlKeysEvent::ePlayPause: {
      RefPtr<MediaControlService> service = MediaControlService::GetService();
      MOZ_ASSERT(service);
      RefPtr<MediaController> controller = service->GetLastAddedController();
      if (!controller) {
        return;
      }

      if (controller->IsPlaying()) {
        controller->Pause();
      } else {
        controller->Play();
      }
      return;
    }
    case MediaControlKeysEvent::eNext:
    case MediaControlKeysEvent::ePrev:
      // TODO : implement related controller functions.
      return;
    default:
      MOZ_ASSERT_UNREACHABLE("Error : undefined event!");
      return;
  }
}

NS_IMPL_ISUPPORTS0(MediaControlKeysEventSource)

void MediaControlKeysEventSource::AddListener(
    MediaControlKeysEventListener* aListener) {
  MOZ_ASSERT(aListener);
  LOG_SOURCE("Add listener %p", aListener);
  mListeners.AppendElement(aListener);
}

void MediaControlKeysEventSource::RemoveListener(
    MediaControlKeysEventListener* aListener) {
  MOZ_ASSERT(aListener);
  LOG_SOURCE("Remove listener %p", aListener);
  mListeners.RemoveElement(aListener);
}

size_t MediaControlKeysEventSource::GetListenersNum() const {
  return mListeners.Length();
}

void MediaControlKeysEventSource::Close() {
  LOG_SOURCE("Close source");
  mListeners.Clear();
}

}  // namespace dom
}  // namespace mozilla
