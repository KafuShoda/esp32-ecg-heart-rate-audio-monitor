# Phase 7: Signal Reliability and Safety Validation

## Objective

The objective of Phase 7 is to evaluate ECG sample continuity, stationary
heart-rate reliability, electrode-disconnection behavior, signal
recovery, and motion-related interference.

This phase will also develop signal-quality protection so unreliable ECG
measurements cannot activate future heart-rate-zone audio prompts.

## Test Progress

- [x] Test 1: Stationary raw ECG baseline
- [x] Test 2: Ten-minute raw-sample continuity
- [x] Test 3: Complete ten-minute stationary BPM and OLED reliability test
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

## Test 2: Ten-Minute Raw-Sample Continuity

### Objective

The objective was to determine whether the Arduino Nano ESP32 could
continuously receive raw ECG samples from the MAX30003 for ten minutes
without a sampling interruption, sensor-communication failure, or
unexpected restart.

### Test Configuration

- Microcontroller: Arduino Nano ESP32
- ECG sensor: ProtoCentral MAX30003
- MAX30003 chip-select pin: D10
- Serial speed: 115200 baud
- Expected sample rate: Approximately 125 samples per second
- Electrode condition: All three electrodes connected
- Test condition: Seated and stationary
- Test duration: 10 minutes

### Method

A dedicated continuity-test sketch counted every raw ECG sample received
from the MAX30003. Once per second, the program reported:

- Samples received during the reporting period
- Cumulative sample count
- Age of the newest sample
- Current streaming status

Evidence was recorded at approximately 60, 300, and 600 seconds.

### Results

| Checkpoint | Samples per second | Total samples | Last-sample age | Status |
|---:|---:|---:|---:|---|
| 1 minute — 60 seconds | 125 | 7,126 | 0 ms | STREAMING |
| 5 minutes — 300 seconds | 125 | 37,126 | 0 ms | STREAMING |
| 10 minutes — 600 seconds | 125 | 74,626 | 0 ms | STREAMING |

Between the one-minute and five-minute checkpoints, 30,000 additional
samples were received over 240 seconds. This corresponds to exactly 125
samples per second.

Between the five-minute and ten-minute checkpoints, 37,500 additional
samples were received over 300 seconds. This also corresponds to exactly
125 samples per second.

The cumulative sample count increased consistently, the last-sample age
remained at 0 ms, and the status remained `STREAMING` at every documented
checkpoint.

### Result

The prototype successfully completed the ten-minute raw-sample
continuity test. No MAX30003 sampling dropout, `NO SAMPLES` condition, or
unexpected restart was observed during the documented run.

The test confirms reliable short-term transfer of raw ECG samples from
the MAX30003 to the Nano ESP32 under stationary conditions. It does not
establish the physiological accuracy of the ECG or heart-rate estimate.

### Evidence

#### One-minute checkpoint

![One-minute continuity checkpoint](../images/phase-7/phase-7-03-continuity-1-minute.png)

The system was receiving 125 samples per second with a last-sample age of
0 ms and a status of `STREAMING`.

#### Five-minute checkpoint

![Five-minute continuity checkpoint](../images/phase-7/phase-7-04-continuity-5-minutes.png)

The cumulative count reached 37,126 samples while acquisition remained
continuous.

#### Ten-minute checkpoint

![Ten-minute continuity checkpoint](../images/phase-7/phase-7-05-continuity-10-minutes.png)

The system reached the ten-minute checkpoint with 74,626 cumulative
samples, a last-sample age of 0 ms, and a status of `STREAMING`.

### Conclusion

Test 2 passed. The MAX30003 and Nano ESP32 maintained continuous raw ECG
sample acquisition at approximately 125 samples per second for the full
ten-minute documented period.

## Test 3: Ten-Minute Stationary BPM and OLED Reliability

### Objective

The objective was to determine whether continuous raw ECG acquisition
could produce stable BPM and R–R estimates for ten minutes while the
participant remained seated and stationary.

The test also checked whether the Serial Monitor and OLED continued
updating without freezing or unexpectedly restarting.

### Test Configuration

- Microcontroller: Arduino Nano ESP32
- ECG sensor: ProtoCentral MAX30003
- Display: 128 × 64 OLED at I2C address `0x3D`
- OLED pins: A2 for SDA and A3 for SCL
- MAX30003 chip-select pin: D10
- Serial speed: 115200 baud
- Electrode condition: All three electrodes connected
- Test condition: Seated and stationary
- Test duration: 10 minutes

### Method

The Phase 6 heart-rate and OLED sketch was copied into a separate Phase
7 test folder and uploaded to the Nano ESP32.

After all three electrodes were connected, the system was allowed to
acquire a plausible heart-rate estimate. The participant then remained
seated and stationary for ten minutes.

Serial Monitor evidence was recorded at approximately 1, 5, and 10
minutes. The output was checked for plausible BPM values, corresponding
R–R intervals, continued updates, signal-loss messages, freezes, and
unexpected restarts.

### Results

| Checkpoint | Visible BPM range | Visible R–R range | Last visible reading | Result |
|---:|---:|---:|---:|---|
| 1 minute | 79–86 BPM | 695–757 ms | 86 BPM / 695 ms | Stable |
| 5 minutes | 78–83 BPM | 718–765 ms | 78 BPM / 765 ms | Stable |
| 10 minutes | 71–82 BPM | 726–835 ms | 78 BPM / 765 ms | Stable |

All documented BPM and R–R pairs were internally consistent with the
approximate relationship:

\[
\text{BPM} \approx \frac{60{,}000}{\text{R–R interval in milliseconds}}
\]

For example, an R–R interval of 765 ms corresponds to approximately
78.4 BPM, which agrees with the displayed value of 78 BPM.

No extreme BPM spikes, `No plausible reading` messages, permanent
output freezes, or unexpected restarts were visible in the documented
checkpoints.

### Evidence

#### One-minute checkpoint

![Stationary BPM at one minute](../images/phase-7/phase-7-06-bpm-1-minute.png)

The one-minute checkpoint showed continuous readings between
approximately 79 and 86 BPM with corresponding R–R intervals.

#### Five-minute checkpoint

![Stationary BPM at five minutes](../images/phase-7/phase-7-07-bpm-5-minutes.png)

The five-minute checkpoint showed a stable group of readings between
approximately 78 and 83 BPM.

#### Ten-minute checkpoint

![Stationary BPM at ten minutes](../images/phase-7/phase-7-08-bpm-10-minutes.png)

The ten-minute checkpoint confirmed that plausible BPM and R–R output
continued through the end of the test.

### Result

Test 3 passed under stationary conditions.

The MAX30003 continued producing plausible heart-rate estimates through
the ten-minute test, and the BPM and R–R values remained mathematically
consistent. The results support short-term stationary reliability but
do not establish medical accuracy or reliability during walking.

Movement reliability, electrode disconnection behavior, and false-reading
rejection will be evaluated separately in later Phase 7 tests.

The OLED continued updating throughout the test and did not remain
permanently frozen on a previous reading.

## Test 4: Electrode Disconnection and Recovery

### Objective

The objective was to characterize how the prototype responds when each
electrode lead is disconnected individually and when all three leads are
disconnected together.

The test evaluated:

- Whether the system recognized signal loss
- Whether disconnected leads produced false BPM estimates
- Whether the OLED and Serial Monitor continued updating
- How long reacquisition required after reconnection
- Whether the system recovered without a manual reset

This was a characterization test. It did not assume that plausible-looking
BPM values obtained with a disconnected electrode represented a valid
heart-rate measurement.

### Test Configuration

- Microcontroller: Arduino Nano ESP32
- ECG sensor: ProtoCentral MAX30003
- Display: 128 × 64 OLED at I2C address `0x3D`
- OLED pins: A2 for SDA and A3 for SCL
- MAX30003 chip-select pin: D10
- Serial speed: 115200 baud
- Tested sketch:
  `code/phase-7-stationary-bpm/phase-7-stationary-bpm.ino`
- Test condition: Seated and stationary
- Power condition: Laptop operating from battery power
- Audio module: Not active
- Number of trials: Two

### Method

Each trial began with all three electrodes attached. The system was
allowed to acquire stable BPM and R–R readings before disconnection
testing began.

The red, yellow, and green leads were then disconnected individually.
For each lead:

1. The other two leads remained attached.
2. Output behavior was observed while the lead remained disconnected.
3. BPM, R–R, acquiring messages, rejected readings, and artifacts were
   recorded.
4. The lead was reconnected.
5. The time required to return to stable output was recorded.

After the individual-lead tests, all three leads were disconnected
together for 60 seconds. All three were then reattached, and final
reacquisition time was recorded.

The Nano ESP32 was not intentionally reset between conditions.

## Trial 1

### Trial 1 Results

| Condition | Behavior while disconnected | Recovery after reconnection |
|---|---|---:|
| All three connected | Normal and stable BPM and R–R readings | N/A |
| Red disconnected | No visible interruption, pause, or acquiring period | Immediate; no measurable delay |
| Yellow disconnected | The system required approximately 50 seconds to produce readings. During the first five minutes, brief extreme readings or a single `No plausible reading` message appeared approximately every 30 seconds. The output appeared more stable after five minutes. | Approximately 38 seconds |
| Green disconnected | `No plausible reading` continued for approximately 4 minutes 20 seconds. Output briefly appeared stable around 4 minutes 40 seconds. Minutes 5–6 were highly unstable. During minutes 7–10, readings were mostly in the 70–80 BPM range but were interrupted approximately every 20 seconds by an extreme value or `No plausible reading`. | Approximately 20 seconds |
| All three disconnected | `No plausible reading` throughout the complete 60-second observation | Approximately 110 seconds |

### Trial 1 Observations

Disconnecting the red lead produced no obvious sustained effect.
Disconnecting the yellow lead produced temporary signal loss followed by
intermittent artifacts. Disconnecting the green lead caused the most
severe degradation and produced delayed periods of apparently normal
but intermittently unstable output.

Disconnecting all three leads caused the program to reject the signal for
the complete 60-second observation. After all three leads were
reattached, the system recovered without a reset, although reacquisition
required approximately 110 seconds.

## Trial 2

### Trial 2 Results

Initial acquisition with all three electrodes attached required
approximately three minutes. Once acquired, BPM and R–R readings remained
normal and stable for approximately three to four minutes.

| Condition | Behavior while disconnected | Recovery after reconnection |
|---|---|---:|
| All three connected | Stable BPM and R–R after approximately three minutes of initial acquisition | N/A |
| Red disconnected | Readings remained stable for three minutes, except for approximately three seconds of abnormal values immediately after disconnection | Effectively immediate; one abnormal low reading appeared for one second after reconnection |
| Yellow disconnected | At 10 seconds the program displayed `No plausible reading`. At 30 seconds it displayed 45 BPM/1328 ms; at 60 seconds, 84 BPM/710 ms; at two minutes, 80 BPM/750 ms; and at three minutes, 88 BPM/679 ms. | `No plausible reading` for approximately 30 seconds, followed by approximately 10 seconds of unreliable readings; reliable output returned after approximately 40 seconds |
| Green disconnected | `No plausible reading` continued for approximately 12 minutes. Scattered BPM estimates appeared during minutes 13–14. During minutes 14–16, readings appeared mostly stable around 75–85 BPM but were interrupted approximately every 20 seconds by an extreme value or `No plausible reading`. | Approximately 30 seconds |
| All three disconnected | `No plausible reading` throughout the complete 60-second observation | Approximately 105 seconds |

### Trial 2 Observations

Trial 2 reproduced the major behavior observed during Trial 1. Removing
red caused almost no sustained change. Removing yellow initially
disrupted acquisition but eventually produced plausible-looking BPM and
R–R values despite the lead remaining disconnected. Removing green
caused the longest and most severe degradation.

The apparently stable values produced with yellow or green disconnected
were not considered verified heart-rate measurements. Their occurrence
demonstrated that numerical plausibility and mathematical consistency
between BPM and R–R were not sufficient to establish signal quality.

The all-leads-off result closely reproduced Trial 1. The program rejected
the signal for the full 60 seconds, and final reacquisition required 105
seconds compared with 110 seconds during Trial 1.

## Comparison Between Trials

| Finding | Trial 1 | Trial 2 | Interpretation |
|---|---:|---:|---|
| Red disconnected | No sustained effect | Only brief transition artifacts | Red disconnection was not reliably identified |
| Yellow reconnected | 38-second recovery | Approximately 40-second recovery | Highly repeatable recovery behavior |
| Green disconnected | Delayed, intermittent false stability | Longer delay followed by intermittent false stability | Same failure pattern with variable timing |
| Green reconnected | 20-second recovery | 30-second recovery | Recovery occurred without a reset |
| All leads disconnected | No plausible reading for 60 seconds | No plausible reading for 60 seconds | Highly repeatable rejection behavior |
| All leads reconnected | 110-second recovery | 105-second recovery | Highly repeatable recovery time |

## Analysis

The two trials produced consistent qualitative results despite
differences in exact timing.

### Red-Lead Disconnection

Red-lead disconnection was not reliably identified. The system continued
producing stable-looking BPM and R–R output with almost no interruption.
This does not prove that the red lead was defective or unnecessary. It
only demonstrates that the current software continued producing
estimates using the remaining connections.

### Yellow-Lead Disconnection

Yellow-lead disconnection initially disrupted acquisition but later
produced plausible-looking BPM and R–R estimates.

For example, Trial 2 produced:

- 45 BPM with an R–R interval of 1328 ms
- 84 BPM with an R–R interval of 710 ms
- 80 BPM with an R–R interval of 750 ms
- 88 BPM with an R–R interval of 679 ms

These pairs were mathematically consistent, but they could not be
considered verified because the yellow lead remained disconnected. This
demonstrated that agreement between BPM and R–R does not independently
confirm ECG signal quality.

### Green-Lead Disconnection

Green-lead disconnection caused the strongest and longest degradation.
Both trials eventually produced periods of plausible-looking output, but
those periods continued to be interrupted by extreme or rejected
readings.

This behavior was classified as false or unverified stability. The large
difference between the two trials' timing also demonstrated that a fixed
waiting period cannot determine whether the signal has become reliable.

### All-Leads-Off Behavior

When all three leads were disconnected, the program displayed
`No plausible reading` throughout both 60-second observations. This was
the desired visible behavior.

After all three leads were reattached, reacquisition required 110 seconds
during Trial 1 and 105 seconds during Trial 2. The close agreement
demonstrated repeatable recovery behavior.

However, the existing sketch used broad BPM and R–R plausibility limits.
The test did not establish that the software positively detected physical
electrode disconnection.

## Test 4 Result

Test 4 successfully characterized electrode-disconnection and recovery
behavior across two trials.

The hardware remained operational and eventually recovered from every
tested condition without an intentional manual reset. However, the
software did not reliably identify individual lead loss and sometimes
accepted plausible-looking estimates while an electrode remained
disconnected.

The results demonstrate that:

- A plausible BPM value does not necessarily indicate a valid ECG signal.
- Brief connection changes can create extreme transient readings.
- Individual lead loss is not reliably detected by numerical limits alone.
- Fixed reacquisition delays cannot guarantee signal validity.
- Previous BPM values must be cleared when signal quality becomes uncertain.
- Audio prompts must remain disabled during poor signal and reacquisition.
- A sustained clean-signal period is required before BPM is accepted.

Signal-quality protection, transient rejection, and a controlled
reacquisition state will be implemented in Test 5.

This prototype is experimental and is not intended for medical use.

### Evidence Note

Test 4 was documented primarily through timed observations recorded in
the results tables. Screenshots were not required because each condition
required continuous monitoring and controlled electrode changes.
