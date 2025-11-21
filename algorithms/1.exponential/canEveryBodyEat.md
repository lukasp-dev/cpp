## Problem: Friends with Severe Allergies

You are hosting a gathering and inviting **N friends**. You can cook **M dishes**, but each friend has certain foods they **cannot eat** due to allergies.  
You need to decide which dishes to prepare so that **every friend can eat at least one dish**.

You are given:

- A list of dishes you can make.
- For each friend, a list showing which dishes they **cannot** eat (marked with `X`).

Below is an example table (Table 4.3).  
An `X` indicates the friend **cannot eat** that dish.

| Friend | Galbijjim | Pizza | Japchae | Tteokbokki | Tangsu-yuk | Dakgangjeong |
|--------|-----------|--------|----------|-------------|-------------|----------------|
| Pei    | O         | X      | O        | X           | O           | O              |
| Jia    | X         | X      | X        | O           | O           | X              |
| Min    | O         | X      | O        | X           | O           | X              |
| Suji   | O         | O      | O        | X           | X           | O              |

**Task:**  
Determine the **minimum number of dishes** you must prepare so that **each friend can eat at least one dish**.

In Table 4.3, there is **no single dish** that all friends can eat.  
Therefore, you must prepare **at least two dishes**.  

For example:

- Pizza + Tangsu-yuk  
- Japchae + Dakgangjeong  
- or any combination where every friend has at least one edible option.