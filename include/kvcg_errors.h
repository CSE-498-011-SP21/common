/****************************************************
 *
 * KVCG Error Codes
 *
 ****************************************************/

#ifndef KVCG_ERROR_CODES_H
#define KVCG_ERROR_CODES_H


/**
 *
 * Definition of KVCG Errors
 *
 */
enum errNum {

KVCG_ESUCCESS = 0,
KVCG_EUNKNOWN = 1,

};

/**
 *
 * Get human readable description of error code
 * returned from KVCG call.
 *
 * @param errnum - error code returned from KVCG call
 *
 * @return description of error
 *
 */
inline const char *kvcg_strerror(errNum errnum) {
    switch (errnum) {
        case KVCG_ESUCCESS: return "Success";
        case KVCG_EUNKNOWN: return "Unknown";
    }

    return "Undefined error";
}

#endif // KVCG_ERROR_CODES_H
