## Test 3: Stationary BPM Reliability

### Objective

The objective was to confirm that the system could continuously calculate and display fresh BPM and R–R interval estimates during a ten-minute stationary test with all three electrodes connected.

### Results

| Time | BPM | R–R interval | OLED updating? | Notes |
|---|---:|---:|:---:|---|
| 1 minute | 80 | 742 ms | Yes | None |
| 2 minutes | 77 | 773 ms | Yes | None |
| 3 minutes | 80 | 750 ms | Yes | None |
| 4 minutes | 81 | 734 ms | Yes | None |
| 5 minutes | 82 | 726 ms | Yes | None |
| 6 minutes | 83 | 718 ms | Yes | None |
| 7 minutes | 74 | 804 ms | Yes | None |
| 8 minutes | 80 | 750 ms | Yes | None |
| 9 minutes | 80 | 742 ms | Yes | None |
| 10 minutes | 80 | 742 ms | Yes | None |

### Results Summary

- Average recorded heart rate: **79.7 BPM**
- Recorded heart-rate range: **74–83 BPM**
- Average R–R interval: **748.1 ms**
- Recorded R–R range: **718–804 ms**
- OLED updates confirmed: **10 out of 10 checkpoints**
- Unexpected restarts: **None observed**
- Prolonged frozen readings: **None observed**
- Acquisition interruptions: **None observed**

The BPM and R–R measurements were mathematically consistent with the relationship:

\[
\text{BPM} \approx \frac{60{,}000}{\text{R–R interval in milliseconds}}
\]

For example, the seven-minute measurement was 74 BPM with an R–R interval of 804 ms:

\[
60{,}000 \div 804 \approx 74.6\text{ BPM}
\]

### Conclusion

The system successfully produced continuous BPM and R–R interval estimates throughout the ten-minute stationary test. The OLED remained operational at every checkpoint, and no freezes, restarts, or acquisition interruptions were observed. This test supports the stationary reliability of the current breadboard prototype under good electrode-contact conditions.

These results evaluate prototype operation and do not establish medical accuracy.
