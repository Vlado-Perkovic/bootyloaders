/**
 * @file potentiometer.c
 *
 * @brief THe file implements behaviour of potentiometer.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "potentiometer.h"
#include "esp_adc/adc_oneshot.h"

//---------------------------------- MACROS -----------------------------------
#define GET_ADC_CHANNEL(value) ((value == 34) ? ADC_CHANNEL_6 : (value == 35) ? ADC_CHANNEL_7 : -1)
#define BITWIDTH               (12)
//-------------------------------- DATA TYPES ---------------------------------
struct _potentiometer_t
{
    uint8_t       pin;
    uint16_t      max_voltage_mv;
    bool          b_is_reversed;
    adc_channel_t e_channel;
};
//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief It configures ADC
 *
 * @param [in] p_ptntmtr a pointer to the potentiometer_t structure.
 *
 * @return Status of initialization.
 */
static esp_err_t _potentiometer_init(potentiometer_t *p_ptntmtr);

/**
 * @brief Allocate memory for a potentiometer_t structure and return a pointer to it
 *
 * @return A pointer to a potentiometer_t struct.
 */
static potentiometer_t *_potentiometer_alloc(void);

/**
 * @brief This function frees the memory allocated for the potentiometer_t structure.
 *
 * @param [in] p_ptntmtr A pointer to the potentiometer_t structure that was created by the _potentiometer_create()
 * function.
 */
static void _potentiometer_free(potentiometer_t *p_ptntmtr);

/**
 * @brief private function that reads and converts the data from the potentiometer
 *
 * @param p_ptntmtr a pointer to the potentiometer_t structure.
 * @return uint32_t a value in interval [0, POTENTIOMETER_MAX_POSITION]
 */
static uint32_t _potentiometer_read_and_convert(potentiometer_t *p_ptntmtr);
//------------------------- STATIC DATA & CONSTANTS ---------------------------
static adc_oneshot_unit_handle_t adc1_handle;
//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------

potentiometer_t *potentiometer_create(uint8_t pin, uint16_t max_voltage_mv, bool b_is_reversed)
{
    potentiometer_t *p_ptntmtr = _potentiometer_alloc();

    if(NULL == p_ptntmtr)
    {
        return NULL;
    }

    p_ptntmtr->pin            = pin;
    p_ptntmtr->max_voltage_mv = max_voltage_mv;
    p_ptntmtr->b_is_reversed  = b_is_reversed;
    p_ptntmtr->e_channel      = GET_ADC_CHANNEL(pin);

    if(-1 == p_ptntmtr->e_channel)
    {
        printf("Invalid channel.\n");
        p_ptntmtr = NULL;
    }

    if(ESP_OK != _potentiometer_init(p_ptntmtr))
    {
        _potentiometer_free(p_ptntmtr);
        p_ptntmtr = NULL;
    }

    return p_ptntmtr;
}

void potentiometer_destroy(potentiometer_t *p_ptntmtr)
{
    if(NULL != p_ptntmtr)
    {
        _potentiometer_free(p_ptntmtr);
    }
}

esp_err_t potentiometer_position_get(potentiometer_t *p_ptntmtr, uint32_t *p_ptntnmtr_position)
{
    esp_err_t err = ESP_OK;
    if(NULL == p_ptntmtr)
    {
        err = ESP_FAIL;
    }

    *p_ptntnmtr_position = (p_ptntmtr->b_is_reversed) ? POTENTIOMETER_MAX_POSITION - _potentiometer_read_and_convert(p_ptntmtr)
                                                      : _potentiometer_read_and_convert(p_ptntmtr);
    return err;
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------
static esp_err_t _potentiometer_init(potentiometer_t *p_ptntmtr)
{
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id  = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten    = ADC_ATTEN_DB_11,
    };

    esp_err_t esp_err = ESP_OK;
    /* only one handle is needed for one adc */
    if(NULL == adc1_handle)
    {
        esp_err = adc_oneshot_new_unit(&init_config1, &adc1_handle);
    }

    if(ESP_OK == esp_err)
    {

        esp_err = adc_oneshot_config_channel(adc1_handle, p_ptntmtr->e_channel, &config);
    }

    return esp_err;
}

static potentiometer_t *_potentiometer_alloc(void)
{
    return (potentiometer_t *)malloc(sizeof(potentiometer_t));
}

static void _potentiometer_free(potentiometer_t *p_ptntmtr)
{
    free(p_ptntmtr);
}

static uint32_t _potentiometer_read_and_convert(potentiometer_t *p_ptntmtr)
{
    int result;
    /* This should be fine */
    adc_oneshot_read(adc1_handle, p_ptntmtr->e_channel, &result);
    if(result < 0)
    {
        result = 0;
    }
    /* result gives us Dout which we scale to [0, POTENTIOMETER_MAX_POSITION].
       2 ^ BITWIDTH represents maximum */
    return (uint32_t)((result * POTENTIOMETER_MAX_POSITION) / (1 << BITWIDTH));
}
//---------------------------- INTERRUPT HANDLERS -----------------------------