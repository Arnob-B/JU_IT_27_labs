# High Level Goal
## Design a system to manage products for a store. Customers can make purchases, and sellers can update the list of products.

## Use Git for version control, and maintain a purchase history of items.

# TODO
- [x] Design a store
 - [ ] CRUD opertions
     - [x] create retailer
     - [x] create customer
     - [x] create item

- [ ] creating users
- [ ] creating retailer
- [ ] creating item
- [ ] creating listing item
- [ ] purchasing item (serial)

- [ ] slap in git for VC
- [ ] make every transaction a git commit


# schema

customer
| field | prop |
| -------------- | --------------- |
| userId | text, PK |
| fname | text |
| lname | text |

retailer
| field | prop |
| -------------- | --------------- |
| userId | text |
| fname | text |
| lname | text |

items
| field | prop |
| -------------- | --------------- |
| id | text |
| name | text |
| quantity | number |
| price | number |


purchases
| field | prop |
| -------------- | --------------- |
| customerId | text,PK |
| itemId | text |
| quantity | number |
| totalPrice | number |

