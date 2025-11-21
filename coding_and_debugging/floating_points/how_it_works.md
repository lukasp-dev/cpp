![Diagram](https://img.notionusercontent.com/s3/prod-files-secure%2F47d0f1a5-2bc8-4793-8739-b93c68e8d157%2Fa99df108-0553-4568-b07b-9b01ce041b50%2Fimage.png/size/w=2000?exp=1763672903&sig=_yrEST2fW0aMGkhHiy37HnaC_aaS7xrcpFMIIOD1hTE&id=2b1a96ff-12e6-80b3-b428-fe2cd5906a5e&table=block&userId=da23ca2d-c48f-4dec-bf37-0ac08848eb83)

### 실수 변수가 저장하는 것들
- 부호 비트(sign bit): 양수인지 음수인지
    - 양수: 0
    - 음수: 1
- 지수(exponent): 소수점을 몇칸 옮겼나?
- 가수(mantissa): 소수점을 옮긴 실수의 최상위 X 비트

**저장 공식:**  
`(-1)^sign × 1.mantissa × 2^(exponent - bias)`

**정규화(normalization):**  
- 소수점 왼쪽이 항상 1이 되도록 조정함  
- 예: `10.75 → 1.34375 × 2^3`

---

### 왜 오차가 생기나?

**가수 비트가 유한함 → 모든 소수를 정확히 저장 불가**  
- 저장 과정에서 반올림 발생  
- 따라서 작게라도 오차가 생기고 누적될 수 있음
- 그래서 두 실수가 같은지 보려면 오차 한도를 정해서 비교하는게 맞음
---

**절대 오차(absolute error):**  
- 큰 값 비교할 때 적절  
- ex) 1,000,000 vs 1,000,003 → 차이 3은 의미 거의 없음

**상대 오차(relative error):**  
- 아주 작은 값 또는 0 근처 비교할 때 필수  
- ex) 0.000001 vs 0.000004 → 절대 차이는 0.000003이지만 상대적으로는 300% 차이

**이유:**  
- 작은 값에서는 절대 오차가 값의 크기에 비해 과도하게 커짐  
- 그래서 상대적인 비율로 비교해야 정확함