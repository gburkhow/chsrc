/** ------------------------------------------------------------
 * SPDX-License-Identifier: GPL-3.0-or-later
 * -------------------------------------------------------------
 * File Authors   : Aoran Zeng <ccmywish@qq.com>
 * Contributors   :  Mr. Will  <mr.will.com@outlook.com>
 * Created On     : <2023-08-30>
 * Major Revision :      2
 * Last Modified  : <2025-07-11>
 * ------------------------------------------------------------*/

/**
 * chsrc get npm
 */
void
pl_nodejs_npm_getsrc (char *option)
{
  chsrc_run ("npm config get registry", RunOpt_No_Last_New_Line);
}


/**
 * @consult https://npmmirror.com/
 *
 * chsrc set npm
 */
void
pl_nodejs_npm_setsrc (char *option)
{
  chsrc_yield_source (pl_nodejs_group);
  if (chsrc_in_standalone_mode())
    chsrc_confirm_source();

  char *cmd = NULL;

  if (chsrc_in_local_mode())
    cmd = xy_2strjoin ("npm config --location project set registry ", source.url);
  else
    cmd = xy_2strjoin ("npm config set registry ", source.url);

  chsrc_run (cmd, RunOpt_No_Last_New_Line);

  if (chsrc_in_standalone_mode())
    {
      chsrc_determine_chgtype (ChgType_Auto);
      chsrc_conclude (&source);
    }
}


/**
 * chsrc reset npm
 */
void
pl_nodejs_npm_resetsrc (char *option)
{
  pl_nodejs_npm_setsrc (option);
}


/**
 * chsrc ls npm
 */
Feature_t
pl_nodejs_npm_feat (char *option)
{
  Feature_t f = {0};

  f.can_get = true;
  f.can_reset = true;

  f.cap_locally = FullyCan;
  f.cap_locally_explain = NULL;
  f.can_english = true;
  f.can_user_define = true;

  f.note = NULL;
  return f;
}

// def_target_gsrf(pl_nodejs_npm);
Target_t pl_nodejs_npm_target = {def_target_inner_gsrf(pl_nodejs_npm),def_target_sourcesn(pl_nodejs_group)};
