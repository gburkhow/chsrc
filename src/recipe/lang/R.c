/** ------------------------------------------------------------
 * SPDX-License-Identifier: GPL-3.0-or-later
 * -------------------------------------------------------------
 * File Authors  : Aoran Zeng <ccmywish@qq.com>
 * Contributors  :  Nil Null  <nil@null.org>
 * Created On    : <2023-09-21>
 * Last Modified : <2025-07-14>
 * ------------------------------------------------------------*/

/**
 * @update 2023-09-04
 *
 * @note
 *   以下注释的，是不含有bioconductor的镜像站，
 *   我们在换cran的同时，也直接帮助用户换bioconductor
 */
static Source_t pl_r_sources[] =
{
  {&UpstreamProvider,  NULL, NULL},
  {&Sjtug_Zhiyuan,    "https://mirrors.sjtug.sjtu.edu.cn/cran/",    DelegateToMirror},
  // {&Ali,           "https://mirrors.aliyun.com/CRAN/",           DelegateToMirror},
  {&Tuna,             "https://mirrors.tuna.tsinghua.edu.cn/CRAN/", DelegateToMirror},
  // {&Sustech,       "https://mirrors.sustech.edu.cn/CRAN",        DelegateToMirror},
  // {&Bfsu,          "https://mirrors.bfsu.edu.cn/CRAN/",          DelegateToMirror},
  // {&Bjtu,          "https://mirror.bjtu.edu.cn/cran/",           DelegateToMirror},
};
def_sources_n(pl_r);


#define PL_R_Config_Windows "~/Documents/.Rprofile"
#define PL_R_Config_POSIX   "~/.Rprofile"

void
pl_r_getsrc (char *option)
{
  /**
   * 或参考：https://zhuanlan.zhihu.com/p/585036231
   *
   * options()$repos
   * options()$BioC_mirror
   */
  if (xy_on_windows)
    {
      chsrc_view_file (PL_R_Config_Windows);
    }
  else
    {
      chsrc_view_file (PL_R_Config_POSIX);
    }
}

/**
 * @consult https://help.mirrors.cernet.edu.cn/CRAN/
 */
void
pl_r_setsrc (char *option)
{
  chsrc_yield_source_and_confirm (pl_r);

  char *bioconductor_url = xy_str_delete_suffix (xy_str_delete_suffix (source.url, "cran/"), "CRAN/");
  bioconductor_url = xy_2strjoin(bioconductor_url, "bioconductor");

  const char *w1 = xy_strjoin (3, "options(\"repos\" = c(CRAN=\"", source.url, "\"))\n" );
  const char *w2 = xy_strjoin (3, "options(BioC_mirror=\"", bioconductor_url, "\")\n" );

  char *w = xy_2strjoin (w1, w2);

  // 或者我们调用 r.exe --slave -e 上面的内容

  char *config = xy_on_windows ? PL_R_Config_Windows : PL_R_Config_POSIX;

  chsrc_append_to_file (w, config);

  chsrc_determine_chgtype (ChgType_Auto);
  chsrc_conclude (&source);
}


Feature_t
pl_r_feat (char *option)
{
  Feature_t f = {0};

  f.can_get = true;
  f.can_reset = false;

  f.cap_locally = CanNot;
  f.cap_locally_explain = NA;
  f.can_english = false;
  f.can_user_define = false;

  f.note = NULL;
  return f;
}

def_target_gsf(pl_r);
