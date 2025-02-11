/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

const PropTypes = require("devtools/client/shared/vendor/react-prop-types");

const browser = {
  // The id of the browser which is defined in MDN compatibility dataset.
  // e.g. "firefox"
  // https://github.com/mdn/browser-compat-data/tree/master/browsers
  id: PropTypes.string.isRequired,
  // The version of this browser.
  // e.g. "70.0"
  version: PropTypes.string.isRequired,
};

const issue = {
  // Type of this issue. The type should be one of MDNCompatibility.ISSUE_TYPE.
  type: PropTypes.string.isRequired,
  // The CSS property which caused this issue.
  property: PropTypes.string.isRequired,
  // The url of MDN documentation for the CSS property.
  url: PropTypes.string.isRequired,
  // Whether the CSS property is deprecated or not.
  deprecated: PropTypes.bool.isRequired,
  // Whether the CSS property is experimental or not.
  experimental: PropTypes.bool.isRequired,
  // The browsers which do not support the CSS property.
  unsupportedBrowsers: PropTypes.arrayOf(PropTypes.shape(browser)).isRequired,
};

exports.issue = issue;
