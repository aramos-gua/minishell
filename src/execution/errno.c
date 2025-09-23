/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:18:20 by aramos            #+#    #+#             */
/*   Updated: 2025/09/23 18:07:04 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_return_val(t_data *all, int ft_errno)
{
	dprintf(2, "finding in haystack");
	if (ft_errno == EPERM)
		all->return_val = 1;
	else if (ft_errno == ENOENT)
		all->return_val = 2;
	else if (ft_errno == ESRCH)
		all->return_val = 3;
	else if (ft_errno == EINTR)
		all->return_val = 4;
	else if (ft_errno == EIO)
		all->return_val = 5;
	else if (ft_errno == ENXIO)
		all->return_val = 6;
	else if (ft_errno == E2BIG)
		all->return_val = 7;
	else if (ft_errno == ENOEXEC)
		all->return_val = 8;
	else if (ft_errno == EBADF)
		all->return_val = 9;
	else if (ft_errno == ECHILD)
		all->return_val = 10;
	else if (ft_errno == EAGAIN)
		all->return_val = 11;
	else if (ft_errno == ENOMEM)
		all->return_val = 12;
	else if (ft_errno == EACCES)
		all->return_val = 13;
	else if (ft_errno == EFAULT)
		all->return_val = 14;
	else if (ft_errno == ENOTBLK)
		all->return_val = 15;
	else if (ft_errno == EBUSY)
		all->return_val = 16;
	else if (ft_errno == EEXIST)
		all->return_val = 17;
	else if (ft_errno == EXDEV)
		all->return_val = 18;
	else if (ft_errno == ENODEV)
		all->return_val = 19;
	else if (ft_errno == ENOTDIR)
		all->return_val = 20;
	else if (ft_errno == EISDIR)
		all->return_val = 21;
	else if (ft_errno == EINVAL)
		all->return_val = 22;
	else if (ft_errno == ENFILE)
		all->return_val = 23;
	else if (ft_errno == EMFILE)
		all->return_val = 24;
	else if (ft_errno == ENOTTY)
		all->return_val = 25;
	else if (ft_errno == ETXTBSY)
		all->return_val = 26;
	else if (ft_errno == EFBIG)
		all->return_val = 27;
	else if (ft_errno == ENOSPC)
		all->return_val = 28;
	else if (ft_errno == ESPIPE)
		all->return_val = 29;
	else if (ft_errno == EROFS)
		all->return_val = 30;
	else if (ft_errno == EMLINK)
		all->return_val = 31;
	else if (ft_errno == EPIPE)
		all->return_val = 32;
	else if (ft_errno == EDOM)
		all->return_val = 33;
	else if (ft_errno == ERANGE)
		all->return_val = 34;
	else if (ft_errno == EDEADLK)
		all->return_val = 35;
	else if (ft_errno == ENAMETOOLONG)
		all->return_val = 36;
	else if (ft_errno == ENOLCK)
		all->return_val = 37;
	else if (ft_errno == ENOSYS)
		all->return_val = 38;
	else if (ft_errno == ENOTEMPTY)
		all->return_val = 39;
	else if (ft_errno == ELOOP)
		all->return_val = 40;
	else if (ft_errno == EWOULDBLOCK)
		all->return_val = EAGAIN;
	else if (ft_errno == ENOMSG)
		all->return_val = 42;
	else if (ft_errno == EIDRM)
		all->return_val = 43;
	else if (ft_errno == ECHRNG)
		all->return_val = 44;
	else if (ft_errno == EL2NSYNC)
		all->return_val = 45;
	else if (ft_errno == EL3HLT)
		all->return_val = 46;
	else if (ft_errno == EL3RST)
		all->return_val = 47;
	else if (ft_errno == ELNRNG)
		all->return_val = 48;
	else if (ft_errno == EUNATCH)
		all->return_val = 49;
	else if (ft_errno == ENOCSI)
		all->return_val = 50;
	else if (ft_errno == EL2HLT)
		all->return_val = 51;
	else if (ft_errno == EBADE)
		all->return_val = 52;
	else if (ft_errno == EBADR)
		all->return_val = 53;
	else if (ft_errno == EXFULL)
		all->return_val = 54;
	else if (ft_errno == ENOANO)
		all->return_val = 55;
	else if (ft_errno == EBADRQC)
		all->return_val = 56;
	else if (ft_errno == EBADSLT)
		all->return_val = 57;
	else if (ft_errno == EBFONT)
		all->return_val = 59;
	else if (ft_errno == ENOSTR)
		all->return_val = 60;
	else if (ft_errno == ENODATA)
		all->return_val = 61;
	else if (ft_errno == ETIME)
		all->return_val = 62;
	else if (ft_errno == ENOSR)
		all->return_val = 63;
	else if (ft_errno == ENONET)
		all->return_val = 64;
	else if (ft_errno == ENOPKG)
		all->return_val = 65;
	else if (ft_errno == EREMOTE)
		all->return_val = 66;
	else if (ft_errno == ENOLINK)
		all->return_val = 67;
	else if (ft_errno == EADV)
		all->return_val = 68;
	else if (ft_errno == ESRMNT)
		all->return_val = 69;
	else if (ft_errno == ECOMM)
		all->return_val = 70;
	else if (ft_errno == EPROTO)
		all->return_val = 71;
	else if (ft_errno == EMULTIHOP)
		all->return_val = 72;
	else if (ft_errno == EDOTDOT)
		all->return_val = 73;
	else if (ft_errno == EBADMSG)
		all->return_val = 74;
	else if (ft_errno == EOVERFLOW)
		all->return_val = 75;
	else if (ft_errno == ENOTUNIQ)
		all->return_val = 76;
	else if (ft_errno == EBADFD)
		all->return_val = 77;
	else if (ft_errno == EREMCHG)
		all->return_val = 78;
	else if (ft_errno == ELIBACC)
		all->return_val = 79;
	else if (ft_errno == ELIBBAD)
		all->return_val = 80;
	else if (ft_errno == ELIBSCN)
		all->return_val = 81;
	else if (ft_errno == ELIBMAX)
		all->return_val = 82;
	else if (ft_errno == ELIBEXEC)
		all->return_val = 83;
	else if (ft_errno == EILSEQ)
		all->return_val = 84;
	else if (ft_errno == ERESTART)
		all->return_val = 85;
	else if (ft_errno == ESTRPIPE)
		all->return_val = 86;
	else if (ft_errno == EUSERS)
		all->return_val = 87;
	else if (ft_errno == ENOTSOCK)
		all->return_val = 88;
	else if (ft_errno == EDESTADDRREQ)
		all->return_val = 89;
	else if (ft_errno == EMSGSIZE)
		all->return_val = 90;
	else if (ft_errno == EPROTOTYPE)
		all->return_val = 91;
	else if (ft_errno == ENOPROTOOPT)
		all->return_val = 92;
	else if (ft_errno == EOPNOTSUPP)
		all->return_val = 95;
	else if (ft_errno == EPFNOSUPPORT)
		all->return_val = 96;
	else if (ft_errno == EAFNOSUPPORT)
		all->return_val = 97;
	else if (ft_errno == EADDRINUSE)
		all->return_val = 98;
	else if (ft_errno == ENETDOWN)
		all->return_val = 100;
	else if (ft_errno == ENETUNREACH)
		all->return_val = 101;
	else if (ft_errno == ENETRESET)
		all->return_val = 102;
	else if (ft_errno == ECONNABORTED)
		all->return_val = 103;
	else if (ft_errno == ECONNRESET)
		all->return_val = 104;
	else if (ft_errno == ENOBUFS)
		all->return_val = 105;
	else if (ft_errno == EISCONN)
		all->return_val = 106;
	else if (ft_errno == ENOTCONN)
		all->return_val = 107;
	else if (ft_errno == ESHUTDOWN)
		all->return_val = 108;
	else if (ft_errno == ETOOMANYREFS)
		all->return_val = 109;
	else if (ft_errno == ETIMEDOUT)
		all->return_val = 110;
	else if (ft_errno == ECONNREFUSED)
		all->return_val = 111;
	else if (ft_errno == EHOSTDOWN)
		all->return_val = 112;
	else if (ft_errno == EHOSTUNREACH)
		all->return_val = 113;
	else if (ft_errno == EALREADY)
		all->return_val = 114;
	else if (ft_errno == EINPROGRESS)
		all->return_val = 115;
	else if (ft_errno == ESTALE)
		all->return_val = 116;
	else if (ft_errno == EUCLEAN)
		all->return_val = 117;
	else if (ft_errno == ENOTNAM)
		all->return_val = 118;
	else if (ft_errno == ENAVAIL)
		all->return_val = 119;
	else if (ft_errno == EISNAM)
		all->return_val = 120;
	else if (ft_errno == EREMOTEIO)
		all->return_val = 121;
	else if (ft_errno == EDQUOT)
		all->return_val = 122;
	else if (ft_errno == ENOMEDIUM)
		all->return_val = 123;
	else if (ft_errno == EMEDIUMTYPE)
		all->return_val = 124;
	else if (ft_errno == ECANCELED)
		all->return_val = 125;
	else if (ft_errno == ENOKEY)
		all->return_val = 126;
	else if (ft_errno == EKEYEXPIRED)
		all->return_val = 127;
	else if (ft_errno == EKEYREVOKED)
		all->return_val = 128;
	else if (ft_errno == EKEYREJECTED)
		all->return_val = 129;
	else if (ft_errno == EOWNERDEAD)
		all->return_val = 130;
	else if (ft_errno == ENOTRECOVERABLE)
		all->return_val = 131;
	else if (ft_errno == ERFKILL)
		all->return_val = 132;
}
