#ifndef __MCABBER_XMPP_MUC_H__
#define __MCABBER_XMPP_MUC_H__ 1

void roompresence(gpointer room, void *presencedata);
void got_muc_message(const char *from, LmMessageNode *x);
void handle_muc_presence(const char *from, LmMessageNode * xmldata,
                         const char *roomjid, const char *rname,
                         enum imstatus ust, const char *ustmsg,
                         time_t usttime, char bpprio);

#endif /* __MCABBER_XMPP_MUC_H__ */

/* vim: set expandtab cindent cinoptions=>2\:2(0:  For Vim users... */