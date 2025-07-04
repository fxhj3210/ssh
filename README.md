# make
		ubuntu
			/etc/pam.d/common-auth  
					auth	required	pam_deny.so
     centos
			/etc/pam.d/sshd
					auth	required	pam_env.so
					auth	required	pam_faildelay.so delay=2000000
				-->	auth	requisite	pam_unix.so nullok try_first_pass
				-->	auth	optional	example.so
					auth	sufficient	pam_unix.so nullok try_first_pass
					auth	requisite	pam_succeed_if.so uid >= 1000 quiet_success
					auth	required	pam_deny.so
