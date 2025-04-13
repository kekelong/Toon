#pragma once

#define TOON_MIN(x, y) (((x) < (y)) ? (x) : (y))
#define TOON_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define TOON_PIN(a, min_value, max_value) TOON_MIN(max_value, TOON_MAX(a, min_value))

#define TOON_VALID_INDEX(idx, range) (((idx) >= 0) && ((idx) < (range)))
#define TOON_PIN_INDEX(idx, range) TOON_PIN(idx, 0, (range)-1)

#define TOON_SIGN(x) ((((x) > 0.0f) ? 1.0f : 0.0f) + (((x) < 0.0f) ? -1.0f : 0.0f))
