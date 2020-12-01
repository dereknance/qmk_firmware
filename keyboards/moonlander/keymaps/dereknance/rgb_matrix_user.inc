RGB_MATRIX_EFFECT(my_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static int christmas_colors[][3] = {
    {RGB_RED},
    {RGB_GREEN},
    {0x00, 0x00, 0x00}
};

static void really_dumb_effect(int i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;

    int color_idx = rand() % 3;
    int *color = christmas_colors[color_idx];
    rgb_matrix_set_color(i, color[0], color[1], color[2]);
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
