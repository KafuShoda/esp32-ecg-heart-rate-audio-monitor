# Phase 7: Signal Reliability and Safety Validation

## Objective

The objective of Phase 7 is to evaluate ECG sample continuity, stationary
heart-rate reliability, electrode-disconnection behavior, signal
recovery, and motion-related interference.

This phase will also develop signal-quality protection so unreliable ECG
measurements cannot activate future heart-rate-zone audio prompts.

## Test Progress

- [x] Test 1: Stationary raw ECG baseline
- [ ] Test 2: Ten-minute raw-sample continuity
- [ ] Test 3: Ten-minute stationary BPM reliability
- [ ] Test 4: Electrode disconnection and recovery
- [ ] Test 5: Implement signal-quality protection
- [ ] Test 6: Verify signal-quality protection
- [ ] Test 7: Controlled movement testing
- [ ] Test 8: Final endurance test

## Test 1: Stationary Raw ECG Baseline

### Objective

The objective was to confirm that the new electrode pads could produce a
repeatable raw ECG waveform while the user remained seated and still.

### Test Configuration

- Microcontroller: Arduino Nano ESP32
- ECG sensor: ProtoCentral MAX30003
- Electrodes: Three new disposable ECG electrode pads
- Serial speed: 115200 baud
- Test condition: Seated and stationary
- Electrode leads connected: Red, yellow, and green

The MAX30003 continued to be checked approximately every 8 milliseconds.
For easier visualization, the sketch averaged four raw samples into each
point sent to Arduino Serial Plotter.

### Procedure

1. All three new electrode pads were attached.
2. The red, yellow, and green cable snaps were connected.
3. Arduino Serial Plotter was opened at 115200 baud.
4. The signal was allowed to settle.
5. The stationary waveform was observed for approximately two minutes.

### Result

A repeating raw ECG waveform was visible with all three electrodes
connected. The slower plotted output made the waveform easier to inspect.

This test confirmed basic raw ECG acquisition under stationary
conditions. It did not evaluate medical accuracy or signal behavior
during movement.

### Evidence

![Stationary raw ECG waveform](../images/phase-7/phase-7-02-raw-baseline.jpeg)
