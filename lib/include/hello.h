/* Copyright (c) 2024 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "pw_containers/flat_map.h"
#include "pw_result/result.h"
#include "pw_status/status.h"
#include "pw_string/string.h"
#include "pw_string/string_builder.h"

namespace app {
void WelcomeMessage(::pw::StringBuilder& buffer,
                    std::string_view greeting,
                    std::string_view name);

/// A single Track in a convenient form for C++ code.
struct Track {
  int64_t id;
  pw::InlineString<CONFIG_APP_TRACK_TITLE_MAX_LEN> title;
  pw::InlineString<CONFIG_APP_TRACK_ARTIST_NAME_MAX_LEN> artist_name;
  int year;
};

/// An in-memory collection of tracks.
/// A TrackDatabase is empty until `AddTrack()` is called.
template <size_t kArraySize>
class TrackDatabase {
 public:
  using value_type = ::pw::containers::Pair<int64_t, Track>;

  /// Build a database with a set of default values
  constexpr TrackDatabase(const std::array<value_type, kArraySize>& items)
      : tracks_(items) {}

  /// Finds a Track by ID, or returns null if not found.
  ///
  /// Any non-null pointer is borrowed, and will be valid until the
  /// TrackDatabase is destroyed.
  ///
  /// NOTE: Returning pointers to *const* Track here allows handing out a
  /// pointer to our internal copy of the Track without concern that the caller
  /// will break the database's invariants by modifying the Track.
  pw::Result<const Track*> FindTrackById(int64_t id) const {
    if (!tracks_.contains(id)) {
      return pw::Status::NotFound();
    }
    return &tracks_.at(id);
  }

 private:
  pw::containers::FlatMap<int64_t, Track, kArraySize> tracks_;
};

#include "pw_containers/vector.h"

constexpr static inline std::array<::pw::containers::Pair<int64_t, Track>, 5>
CannedTracks() {
  return {
      ::pw::containers::Pair{int64_t{1},
                             Track{
                                 .id = int64_t{1},
                                 .title = "Money for Mumbling Monkeys",
                                 .artist_name = "Dire Music",
                                 .year = 1974,
                             }},
      {int64_t{2},
       Track{
           .id = int64_t{2},
           .title = "C++101 in the key of C#",
           .artist_name = "(confused devs)",
           .year = 2001,
       }},
      {int64_t{3},
       Track{
           .id = int64_t{3},
           .title = "Department of Redundancy Department",
           .artist_name = "Department of Redundancy Department",
           .year = 2020,
       }},
      {int64_t{42},
       Track{
           .id = int64_t{42},
           .title = "Life, the Universe, and Everything",
           .artist_name = "Douglas Adams",
           .year = 1952,
       }},
      {int64_t{123},
       Track{
           .id = int64_t{123},
           .title = "Rain From Heaven",
           .artist_name = "Sisterhood",
           .year = 1986,
       }},
  };
}
}  // namespace app
