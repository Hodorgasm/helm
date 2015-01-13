/* Copyright 2013-2014 Little IO
 *
 * mopo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mopo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mopo.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "mopo.h"
#include "value.h"
#include <cmath>

namespace mopo {

  namespace {
    const mopo_float EPSILON = 1e-16;
    const mopo_float DB_GAIN_CONVERSION_MULT = 40.0;
    const mopo_float MIDI_0_FREQUENCY = 8.1757989156;
    const int NOTES_PER_OCTAVE = 12;
    const int CENTS_PER_NOTE = 100;
    const int CENTS_PER_OCTAVE = NOTES_PER_OCTAVE * CENTS_PER_NOTE;
    const int MAX_CENTS = MIDI_SIZE * CENTS_PER_NOTE;
  }

  namespace utils {

    const Value value_zero(0.0);
    const Value value_one(1.0);
    const Value value_two(2.0);
    const Value value_pi(PI);
    const Value value_2pi(2.0 * PI);
    const Value value_neg_one(-1.0);

    inline bool closeToZero(mopo_float value) {
      return value <= EPSILON && value >= -EPSILON;
    }

    inline mopo_float gainToDb(mopo_float gain) {
      return DB_GAIN_CONVERSION_MULT * log10(gain);
    }

    inline mopo_float dbToGain(mopo_float decibals) {
      return std::pow(10.0, decibals / DB_GAIN_CONVERSION_MULT);
    }

    inline mopo_float midiCentsToFrequency(mopo_float cents) {
      return MIDI_0_FREQUENCY * pow(2.0, cents / CENTS_PER_OCTAVE);
    }

    inline mopo_float midiNoteToFrequency(mopo_float note) {
      return midiCentsToFrequency(note * CENTS_PER_NOTE);
    }

    inline mopo_float frequencyToMidiNote(mopo_float frequency) {
      return NOTES_PER_OCTAVE * log2(frequency / MIDI_0_FREQUENCY);
    }

    inline mopo_float frequencyToMidiCents(mopo_float frequency) {
      return CENTS_PER_NOTE * frequencyToMidiNote(frequency);
    }

    inline bool isSilent(const mopo_float* buffer, int length) {
      for (int i = 0; i < length; ++i) {
        if (!closeToZero(buffer[i]))
          return false;
      }
      return true;
    }
  } // namespace utils
} // namespace mopo

#endif // UTILS_H
