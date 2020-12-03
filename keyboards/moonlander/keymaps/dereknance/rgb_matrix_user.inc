RGB_MATRIX_EFFECT(my_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static int christmas_colors[][3] = {
    {0, 255}, // red
    {85, 255}, // green
    {0, 0} // white
};

static void really_dumb_effect(int i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;

    // if init or random number is even,
    //   pick a random color red, green, or white
    // else
    //   extinguish the light (value/brightness == 0)

    HSV hsv = {0, 0, 0};
    if (params->init || (rand() % 6 != 0)) {
        int hsv_idx = rand() % 3;
        hsv.h = christmas_colors[hsv_idx][0];
        hsv.s = christmas_colors[hsv_idx][1];
        hsv.v = rgb_matrix_config.hsv.v;
    } else {
        hsv.h = rgb_matrix_config.hsv.h;
        hsv.s = rgb_matrix_config.hsv.s;
        hsv.v = 0;
    }

    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool my_effect(effect_params_t* params) {
    if (!params->init) {
        // Change one LED every tick, make sure speed is not 0
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 10 == 0) {
            really_dumb_effect(rand() % DRIVER_LED_TOTAL, params);
        }
        return false;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (int i = led_min; i < led_max; i++) {
        really_dumb_effect(i, params);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
