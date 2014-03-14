/*!CK:704809917!*//*1393839652,178191663*/

if (self.CavalryLogger) { CavalryLogger.start_js(["LI3WA"]); }

__d("ActivityLogBulkSelection",["Event","AsyncRequest","CSS","DataStore","DOM","DOMDimensions","DOMScroll","Parent","arrayContains","copyProperties","csx","cx","fbt","getElementPosition","removeFromArray"],function(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u){var v=10,w='fbTimelineLogBody',x='ActivityLogBulkSelection-instance',y='ActivityLogBulkSelection-ids',z=false;function aa(ga){return k.find(ga,"input._2o3s");}function ba(ga){return k.scry(ga,"input._2o3s");}function ca(ga){return n.byClass(ga,"_z6m");}function da(ga,ha){this._sidenav=ga;this._body=k.find(ha,'.'+w);j.set(this._body,x,this);this._selected=[];g.listen(this._body,'click',function(event){var ka=ca(event.getTarget());if(!ka)return;if(!aa(ka).checked){u(this._selected,ka);}else if(!o(this._selected,ka))this._selected.push(ka);this._selectionChanged();if(z)i.conditionClass(ka,"_5lq9",aa(ka).checked);}.bind(this));if(z){var ia=k.find(this._sidenav,"a._5lqb");}else ia=k.find(this._sidenav,"a._2o3u");g.listen(ia,'click',function(){this._selected.forEach(function(ka){aa(ka).checked=false;if(z)i.removeClass(ka,"_5lq9");});this._selected=[];this._selectionChanged();}.bind(this));ba(this._body).forEach(function(ka){ka.checked&&this._selected.push(ca(ka));}.bind(this));var ja;if(z){this._selectButton=k.find(this._sidenav,"._5lqc");this._doneButton=k.find(this._sidenav,"._5lqd");this._submitButton=k.find(this._sidenav,"._5lqe");this._noTaggedPhotosMessage=k.find(this._sidenav,"._5lv7");g.listen(this._selectButton,'click',function(){this._swapBulkButtons(this._selectButton,this._doneButton,true);var ka=ba(this._body);if(ka.length===0){i.show(this._noTaggedPhotosMessage);}else{var la=ka[0],ma=false;for(var na=0;na<ka.length;na++)if(fa(ka[na])){ma=true;break;}if(!ma)m.scrollTo(la,true,true);}}.bind(this));g.listen(this._doneButton,'click',function(){i.hide(this._noTaggedPhotosMessage);this._swapBulkButtons(this._doneButton,this._selectButton,false);}.bind(this));ja=this._submitButton;}else ja=k.find(this._sidenav,"._2o3v");g.listen(ja,'click',function(){new h('/ajax/photo_tag/bulk_remove').setData({photo_ids:this.getSelectedIDs()}).send();}.bind(this));this._selected.length&&this._selectionChanged();}da.init=function(ga,ha,ia,ja){v=ia;z=ja;return new da(ga,ha);};da.registerStory=function(ga,ha){j.set(ga,y,ha);var ia=n.byClass(ga,w),ja=j.get(ia,x);if(ja&&ja._checkboxesDisabled)ea(ga,true);};p(da.prototype,{getSelectedIDs:function(){var ga={};this._selected.forEach(function(ha){var ia=j.get(ha,y);ia&&ia.forEach(function(ja){ga[ja]=true;});});return Object.keys(ga);},_selectionChanged:function(){var ga=this._selected.length,ha="span._2o3w";if(z){ha="span._5lqf";i.hide(this._noTaggedPhotosMessage);}var ia=k.find(this._sidenav,ha);if(ga>1){k.setContent(ia,s._("{num} items",[s.param("num",ga)]));}else if(ga==1)k.setContent(ia,"1 item");if(z){i.conditionClass(this._sidenav,"_5lqa",ga);i.conditionShow(this._doneButton,!ga);i.conditionShow(this._submitButton,ga);}else i.conditionClass(this._sidenav,"_2o3r",ga);var ja=this._checkboxesDisabled;this._checkboxesDisabled=this._selected.length>=v;if(!ja&&this._checkboxesDisabled){ea(this._body,true);}else if(ja&&!this._checkboxesDisabled)ea(this._body,false);},_swapBulkButtons:function(ga,ha,ia){i.hide(ga);i.show(ha);i.conditionClass(this._body,"_2o47",ia);}});function ea(ga,ha){ba(ga).forEach(function(ia){if(!ia.checked)ia.disabled=ha;});}function fa(ga){var ha=l.getViewportDimensions().height,ia=t(ga);return ia.y<ha&&ia.y>0;}e.exports=da;});
__d("ActivityLogOptionButton",["Button","csx","DOMQuery","SelectableMenu","Tooltip"],function(a,b,c,d,e,f,g,h,i,j,k){var l;function m(n,o,p){this._root=n;this._popoverMenu=o;var q=this._popoverMenu.subscribe('setMenu',function(){this._menu=this._popoverMenu.getMenu();if(this._menu instanceof j){q.unsubscribe();this._menu.subscribe('change',function(event,r){var s=i.find(n,"._2fmm");k.set(s,r.label);var t;if(r.value=='allow'||r.value=='default_allow'){t=l&&l.cloneNode(true);}else t=r.item.getIcon().cloneNode(true);g.setIcon(s,t);});}}.bind(this));}m.registerPencilIcon=function(n){l=n;};e.exports=m;});
__d("AllActivityContentLoader",["ActivityLogScrubberConfig","Arbiter","CSS","DOM","DOMScroll","OnVisible","Parent","ScrollingPager","TimelineConstants","TimelineController","TimelineLegacySections","TimelineSmartInsert","UIPagelet","Vector","$","clickRefAction","copyProperties","csx","userAction"],function(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y){var z=false,aa=0,ba=null,ca={},da=[],ea={},fa=[],ga=null,ha=null;function ia(ma,na,oa,pa,qa){this.node=ma;this.canScrollLoad=true;this.scrubberKey=na;this._pageletLoadData=oa;this.loaded=pa;this.sortKey=qa;this.contentNode=j.scry(ma,"div._z6j")[0];}function ja(){if(z)return;p.register(p.CONTENT,la);ga=y('allactivity').uai('init','scrubber',false);v('scrubber').set_namespace('allactivity');z=true;}function ka(ma){var na=q.get(ma);na&&na.canScrollLoad&&na.load();}w(ia.prototype,{load:function(){if(this.loaded)return;this.loaded=true;this.contentNode&&i.hide(this.contentNode);i.show(m.byClass(this.node,'fbTimelineSection'));var ma=g.gkResults?'TimelineEntStoryActivityLogPagelet':'TimelineProfileAllActivityPagelet',na=this.node;function oa(qa){r.run(na,qa);}var pa=j.find(this.node,'div.fbTimelineLogStream');fa.push(s.loadFromEndpoint(ma,pa.id,this._pageletLoadData,{usePipe:true,jsNonblock:true,constHeight:true,displayCallback:oa,append:true}));},contentAdded:function(ma){if(!this.hasContent){i.removeClass(m.byClass(this.node,'stat_elem'),'async_saving');if(this.contentNode){ma&&j.prependContent(this.contentNode,ma);i.show(this.contentNode);}this.hasContent=true;}},fullyLoaded:function(){if(!this.hasContent){i.removeClass(m.byClass(this.node,'stat_elem'),'async_saving');i.show(j.find(this.node,"div._40pu"));this.contentNode&&i.hide(this.contentNode);}},activateScrollLoad:function(){this.canScrollLoad=true;ea[this.scrubberKey]&&ea[this.scrubberKey].reset();},deactivateScrollLoad:function(){if(!this.loaded){this.canScrollLoad=false;}else{var ma=j.scry(this.node,'div.all_activity_pager')[0];if(ma){var na=n.getInstance(ma.id);if(na){na.removeOnVisible();i.removeClass(j.scry(ma,'div.uiMorePager')[0],'async_saving');}}}ea[this.scrubberKey]&&ea[this.scrubberKey].remove();},getParent:function(){if(this.parentKey)return q.get(this.parentKey);return null;}});var la={SCROLL_TO_OFFSET:115,HEADER_SCROLL_CUTOFF:30,CURRENT_SECTION_OFFSET:150,registerTimePeriod:function(ma,na,oa,pa,qa,ra){ja();var sa=new ia(ma,na,oa,pa,ra);if(!qa){da.push(na);ca[na]=true;}else{sa.parentKey=qa;q.get(qa).subSections=q.get(qa).subSections||[];q.get(qa).subSections.push(sa);q.get(qa).subSections.sort(function(ta,ua){return ua.sortKey-ta.sortKey;});}q.set(na,sa);la.checkCurrentSectionChange();h.inform(o.SECTION_REGISTERED,{scrubberKey:na},h.BEHAVIOR_PERSISTENT);},reset:function(){la.stopLoadingContent();z=false;q.removeAll();aa=0;ba=null;ca={};da=[];ea={};fa=[];ga=null;ha=null;},stopLoadingContent:function(){for(var ma in ea)ea[ma]&&ea[ma].remove();for(var na=0;na<fa.length;na++)fa[na].cancel();},setContentHeader:function(ma){ha=ma;},checkCurrentSectionChange:function(){var ma=la.getCurrentSection(),na=ba&&ba.scrubberKey;if(ma&&ma.scrubberKey!==na){ba=ma;var oa=ma.scrubberKey,pa=ma.parentKey;if(!pa){pa=oa;oa=null;}p.sectionHasChanged(pa,oa);}},getCurrentSection:function(){var ma={},na=q.getAll();for(var oa in na){var pa=na[oa];if(!pa.loaded)continue;var qa=t.getElementPosition(pa.node,'viewport').y;if(qa<la.CURRENT_SECTION_OFFSET)ma[qa]=pa;}var ra=Math.max.apply(this,Object.keys(ma)),sa=ra==-Infinity;if(!sa){return ma[ra];}else return null;},enableScrollLoad:function(ma,na,oa){ma=u(ma);var pa=la.getNextSectionKey(na);if(pa)ea[pa]=new l(ma,ka.bind(null,pa),false,oa||1000);},getNextSectionKey:function(ma){var na=q.get(ma),oa=na.getParent(),pa=null,qa=null;if(oa)for(var ra=0;ra<oa.subSections.length-1;ra++)if(oa.subSections[ra].scrubberKey==ma)pa=oa.subSections[ra+1].scrubberKey;if(!pa)for(var sa=0;sa<da.length-sa;sa++)if(da[sa]==oa.scrubberKey){qa=q.get(da[sa+1]).subSections[0];if(qa)pa=qa.scrubberKey;}return pa;},navigateToSection:function(ma,na,oa){ga.add_event("nav_"+ma);na=!!na;var pa=q.get(ma);if(!pa)return;if(!pa.getParent()){ma=pa.subSections[0].scrubberKey;pa=q.get(ma);}for(var qa=0;qa<da.length;qa++){var ra=q.get(da[qa]);for(var sa=0;sa<ra.subSections.length;sa++){if(ra.subSections[sa].scrubberKey==ma)break;ra.subSections[sa].deactivateScrollLoad();}if(ra.scrubberKey==pa.getParent().scrubberKey)break;}pa.activateScrollLoad();pa.load();la.adjustContentPadding();var ta=t.getScrollPosition().x,ua=t.getElementPosition(pa.node).y;if(!na){var va=la.SCROLL_TO_OFFSET;k.scrollTo(new t(ta,ua-va,'document'));}},adjustContentPadding:function(){u('fbTimelineLogBody').style.paddingBottom=t.getViewportDimensions().y-la.CURRENT_SECTION_OFFSET-la.HEADER_SCROLL_CUTOFF+'px';},sectionHasContent:function(ma){var na=q.get(ma);na&&na.contentAdded(ha);ha=null;},sectionFullyLoaded:function(ma){var na=q.get(ma);na&&na.fullyLoaded();}};e.exports=la;});
__d("NotificationsSelector",["Parent","submitForm"],function(a,b,c,d,e,f,g,h){function i(j,k,l){k.subscribe('change',function(m,n){l.value=n.value;var o=g.byTag(j,'form');o&&h(o);});}e.exports.bindForm=i;});
__d("FlexibleScrollableArea",["DataStore","DOM","Event","Parent","Run","Style","Vector","throttle"],function(a,b,c,d,e,f,g,h,i,j,k,l,m,n){var o=30,p=100;function q(r,s,t,u,v){"use strict";this._element=r;this._tight=s;this._measureFrom=t;this._minHeight=u;this._margin=v;g.set(this._element,'FlexibleScrollableArea',this);k.onLeave(this.cleanup.bind(this));this._listener=i.listen(window,'resize',n(this.poke,p,this));this.poke();}q.prototype.poke=function(){"use strict";var r=h.find(this._element,'div.elasticContainer'),s=m.getElementDimensions(r).y,t;if(this._tight){t=Math.max(Math.min(s,this.getMaxHeight()),this._minHeight);var u=m.getElementPosition(r).y+m.getElementDimensions(r).y-m.getElementPosition(this._element).y-t;if(u<=o)t+=u;}else t=Math.max(this.getMaxHeight(),this._minHeight);l.set(this._element,'height',t+'px');};q.prototype.getMaxHeight=function(){"use strict";if(this._measureFrom==='bottom'){var r=m.getViewportDimensions().y,s=m.getElementPosition(this._element,'viewport').y,t=r-s;return t-this._margin;}var u=m.getElementPosition(this._element,'viewport').y+m.getElementDimensions(this._element).y;return u-this._margin;};q.prototype.cleanup=function(){"use strict";this._listener&&this._listener.remove();};q.getInstance=function(r){"use strict";var s=j.byClass(r,'flexibleScrollableArea');return s?g.get(s,'FlexibleScrollableArea'):null;};e.exports=q;});
__d("PopoverMenuDynamicIcon",["Button","CSS","DOM","DOMQuery","copyProperties","csx"],function(a,b,c,d,e,f,g,h,i,j,k,l){function m(n){"use strict";this._popoverMenu=n;}m.prototype.enable=function(){"use strict";this._setMenuSubscription=this._popoverMenu.subscribe('setMenu',this._onSetMenu.bind(this));};m.prototype.disable=function(){"use strict";this._popoverMenu.unsubscribe(this._setMenuSubscription);this._setMenuSubscription=null;this._removeChangeSubscription();};m.prototype._onSetMenu=function(){"use strict";this._removeChangeSubscription();this._menu=this._popoverMenu.getMenu();this._changeSubscription=this._menu.subscribe('change',function(n,o){var p=o.item;if(o[0])p=o[0].item;if(!p)return;var q=p.getIcon();q=q?q.cloneNode(true):null;var r=this._popoverMenu.getTriggerElem(),s=j.scry(r,"span._55pe")[0];if(s){var t=s.firstChild;if(h.hasClass(t,'img')){i.replace(t,q);}else i.prependContent(s,q);}else g.setIcon(r,q);}.bind(this));};m.prototype._removeChangeSubscription=function(){"use strict";if(this._changeSubscription){this._menu.unsubscribe(this._changeSubscription);this._changeSubscription=null;}};k(m.prototype,{_setMenuSubscription:null,_changeSubscription:null});e.exports=m;});
__d("HideInlineHelp",["DynamicIconSelector","SelectorDeprecated"],function(a,b,c,d,e,f,g,h){var i=[],j={registerMenu:function(k,l,m){i[k]=l.setValue.bind(l,m);},registerLegacyMenu:function(k,l,m){i[k]=function(){h.setSelected(l,m);g.swapIcon(l);};},registerAsyncPopoverMenu:function(k,l,m){i[k]=function(){var n=l.getMenu();n.setValue(m);};},triggerUndo:function(k){i[k]();}};e.exports=j;});
__d("TimelineAllActivitySideNav",["CSS","DOM","DOMDimensions","FutureSideNav","PageTransitions","Style","UIPagelet","$","copyProperties","csx"],function(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p){var q={init:function(r,s,t,u){var v=h.find(n('contentArea'),"._6-0"),w=h.getID(v);l.set(v,'minHeight',i.getViewportDimensions().height+'px');g.addClass(r,'fixed_elem');k.registerHandler(function(x){if(s===x.getPath()&&x.getQueryData().sk==t){var y=o({profile_id:u,renderContentsOnly:1,uripath:x.toString()},x.getQueryData()),z=j.getInstance(),aa=z&&z._getItemForKey(y.log_filter);aa&&z.setLoading(aa);m.loadFromEndpoint('TimelineAllActivityColumn',w,y,{jsNonblock:true,constHeight:true,displayCallback:function(ba){ba();aa&&z.setSelected(aa);document.body.scrollTop=0;k.transitionComplete(true);}});return true;}return false;});}};e.exports=q;});
__d("TimelineAllActivityStorySelector",["Arbiter","CSS","PrivacyConst","SelectorDeprecated"],function(a,b,c,d,e,f,g,h,i,j){j.subscribe('select',function(l,m){if(!h.hasClass(m.selector,'fbTimelineAllActivityStorySelector'))return;var n=j.getOptionValue(m.option);if(n==i.BaseValue.CUSTOM){j.toggle(m.selector);return false;}if(h.hasClass(m.option,'fbPrivacyAudienceSelectorOption')){k(m.selector,'fbPrivacyAudienceSelectorOption');}else if(h.hasClass(m.option,'fbTimelineCurationOption'))k(m.selector,'fbTimelineCurationOption');});g.subscribe('CustomPrivacyOptionController/update',function(l,m){if(!h.hasClass(m.selector,'fbTimelineAllActivityStorySelector'))return;k(m.selector,'fbPrivacyAudienceSelectorOption');j.setSelected(m.selector,j.getOptionValue(m.option));});function k(l,m){j.getOptions(l).forEach(function(n){if(h.hasClass(n,m)){var o=j.getOptionValue(n);j.setSelected(l,o,false);}});}});
__d("SelectorSubmitOnChange",["Parent","copyProperties","submitForm"],function(a,b,c,d,e,f,g,h,i){function j(k){"use strict";this._selector=k;}j.prototype.enable=function(){"use strict";this._subscription=this._selector.subscribe('change',this._onChange.bind(this));};j.prototype.disable=function(){"use strict";this._subscription.unsubscribe();this._subscription=null;};j.prototype._onChange=function(){"use strict";var k=g.byTag(this._selector.getButton(),'form');k&&i(k);};h(j.prototype,{_subscription:null});e.exports=j;});