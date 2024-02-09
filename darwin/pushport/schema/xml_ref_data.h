//
// Created by eddie on 09/02/24.
//

#ifndef FM28L_XML_REF_DATA_H
#define FM28L_XML_REF_DATA_H

#define DARWIN_CISSOURCECODE_STRING_LENGTH   4
#define DARWIN_CISSOURCECODE_BYTES_LENGTH   (DARWIN_CISSOURCECODE_STRING_LENGTH + 1)
/**
 * \struct CISSourceCode
 * \brief A CIS source code
 */
typedef struct {
    char string[DARWIN_CISSOURCECODE_BYTES_LENGTH];
} CISSourceCode;

#define DARWIN_CISSOURCENAME_MIN_STRING_LENGTH   0
#define DARWIN_CISSOURCENAME_MAX_STRING_LENGTH   4
#define DARWIN_CISSOURCENAME_MAX_BYTES_LENGTH   (DARWIN_CISSOURCENAME_MAX_STRING_LENGTH + 1)
/**
 * \struct CISSourceName
 * \brief A CIS source name
 */
typedef struct {
    char string[DARWIN_CISSOURCENAME_MAX_BYTES_LENGTH];
} CISSourceName;

/**
 * \struct CISSource
 * \brief Defines the mapping between 4 letter CIS codes and the CIS name
 */
typedef struct{
    CISSourceCode code; ///< This is the 4 letter CIS code
    CISSourceName name; ///< The CIS name
} CISSource;

#endif //FM28L_XML_REF_DATA_H
