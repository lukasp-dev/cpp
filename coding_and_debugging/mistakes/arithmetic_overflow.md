### Arithmetic Overflow
- an overflow during execution
    - getLCM function takes two `int` as parameters.
    - but mid execution, a*b 가 32-bit integer의 상한을 넘어버린다.
    - 그래서 하위 32 bit 만 고려해서 엉뚱한 값이 나옴.
- recurrence avoids overflow
  - factorial formulas produce enormous intermediate values (e.g., n!)
  - recurrence (`C(n,k) = C(n-1,k-1) + C(n-1,k)`) only handles small incremental values
  - prevents explosive growth and greatly reduces overflow risk

### Why CP uses `const int INF = 987654321`

- **Overflow 안전함**: `INT_MAX`보다 충분히 작아서 `INF + INF` 같은 연산도 int 범위 안에 들어감.  
- **입력·식별 쉬움**: 987654321은 키보드 숫자열을 그대로 내려친 형태라 빠르고 오타가 거의 없음.  
- **정수 literal**: `1e9`처럼 double literal 변환 문제가 없음.  
- **실전에서 적당히 큰 값**: Dijkstra/Floyd 등에서 “무한대 역할을 하기에 충분히 크면서도 위험하지 않은 값”.

